#define MOD_SERVER
#include "includes.h"

// shared
#include "components.h"
#include "extensions.h"
#include "api/api.h"

struct mod_t {
    m2o_api_vtable api;

    struct {
        std::string hostname;
        std::string password;
    } settings;
};

static mod_t mod;
librg_ctx_t *ctx;

// server modules
#include "core/settings.h"
#include "core/vehicle.h"
#include "core/pedestrian.h"
#include "core/plugins.h"
#include "core/router.h"

#include "api/errors.h"
#include "api/vehicle.h"
#include "api/pedestrian.h"

/* simple bandwidth measurer */
void mod_measure(void *user_data) {
    librg_ctx_t *ctx = (librg_ctx_t *)user_data;

    if (!ctx || !ctx->network.host) return;

    static u32 lastdl = 0;
    static u32 lastup = 0;

    f32 dl = (ctx->network.host->totalReceivedData - lastdl) * 8.0f / (1000.0f * 1000); // mbps
    f32 up = (ctx->network.host->totalSentData - lastup)     * 8.0f / (1000.0f * 1000); // mbps

    lastdl = ctx->network.host->totalReceivedData;
    lastup = ctx->network.host->totalSentData;

    mod_log("librg_update: took %.3f ms. Current used bandwidth D/U: (%.3f / %.3f) mbps. \r", ctx->last_update, dl, up);
}

int main() {
    const char *test = \
        "===============    M2O-SERVER    =================\n" \
        "==                                              ==\n" \
        "==                 ¯\\_(ツ)_/¯                   ==\n" \
        "==                                              ==\n" \
        "==================================================\n";
    zpl_printf("%s", test);

    // allocate ctx
    ctx = new librg_ctx_t;
    zpl_zero_item(ctx);

    /* fill up default settings */
    ctx->mode            = LIBRG_MODE_SERVER;
    ctx->tick_delay      = MOD_SERVER_TICK_DELAY;
    ctx->world_size      = zplm_vec3f(5000.0f, 5000.0f, 0.0f);
    ctx->max_entities    = MOD_ENTITY_LIMIT;
    ctx->max_connections = 1000;

    librg_address_t address = { 27010, NULL };
    settings_read(ctx, &address, &mod);

    mod_log("starting on port: %u with conn: %u\n", address.port, ctx->max_connections);
    mod_log("my hostname: %s, my password: %s\n", mod.settings.hostname.c_str(), mod.settings.password.c_str());
    mod_log("server tick_delay: %f\n", ctx->tick_delay);

    librg_init(ctx);
    mod_register_routes(ctx);

    zpl_timer_t *tick_timer = zpl_timer_add(ctx->timers);
    tick_timer->user_data = (void *)ctx; /* provide ctx as a argument to timer */
    zpl_timer_set(tick_timer, 1000 * 1000, -1, mod_measure);
    zpl_timer_start(tick_timer, 1000);

    librg_network_start(ctx, address);

    m2o_api_init(&mod.api);
    m2o_plugins_init(&mod.api);

    while (true) {
        librg_tick(ctx);
        zpl_sleep_ms(5);
    }

    librg_network_stop(ctx);
    librg_free(ctx);
    delete ctx;

    return 0;
}
