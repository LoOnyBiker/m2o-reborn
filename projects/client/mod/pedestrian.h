// =======================================================================//
// !
// ! Generic entity events
// !
// =======================================================================//

/**
 * The entity enters the stream zone
 */
void module_ped_callback_create(librg_event_t *event) {
    auto ped = new ped_t();

    ped->model = librg_data_ru16(event->data);
    ped->state = librg_data_ru8(event->data);
    auto namelen = librg_data_ru8(event->data);
    librg_data_rptr(event->data, ped->name, namelen);

    // state on the moment player is created
    if (ped->state == PED_IN_CAR || ped->state == PED_ENTERING_CAR) {
        ped->target_entityid = librg_data_ru32(event->data);
        ped->state  = PED_ENTERING_CAR;
        ped->seat   = librg_data_ru8(event->data);
    }

    event->entity->flags |= MOD_ENTITY_INTERPOLATED;
    event->entity->user_data = ped;

    M2::C_Entity *entity = M2::Wrappers::CreateEntity(M2::eEntityType::MOD_ENTITY_PED, ped->model);

    if (entity->IsActive()) {
        print_posm(event->entity->position, "[info] creating ped at");
        ped->CEntity = entity;
        ped->CEntity->SetPosition(event->entity->position);
        ped->CHuman->GetScript()->SetDemigod(true); /* peds can be killed only from local client side */
    } else {
        mod_log("[warning] could not create a ped for entity: %d\n", event->entity->id);
    }
}

/**
 * The entity exists the stream zone
 */
void module_ped_callback_remove(librg_event_t *event) {
    if (event->entity->id == mod.player->id) return;
    mod_log("destroying ped entity %d\n", event->entity->id);
    auto ped = get_ped(event->entity);

    if (ped->CEntity) { /* maybe it was deleted when we removed car from streamzone */
        M2::Wrappers::DestroyEntity(ped->CEntity, M2::eEntityType::MOD_ENTITY_PED);
        ped->CEntity = nullptr;
    }

    delete ped;
}

// =======================================================================//
// !
// ! Update/sync entity events
// !
// =======================================================================//

void module_ped_tasks_update(ped_t *ped) {
    if (ped->state == PED_ENTERING_CAR && ped->target_entityid != M2O_INVALID_ENTITY) {
        if (librg_entity_valid(ctx, ped->target_entityid)) {
            mod_log("[info] found a valid car, trying to put player ped in");

            ped->vehicle = librg_entity_fetch(ctx, ped->target_entityid);
            auto car = get_car(ped->vehicle);

            M2::C_SyncObject *pSyncObject = nullptr;
            ((M2::C_Human2 *)ped->CEntity)->GetScript()->ScrDoAction(
                &pSyncObject, (M2::C_Vehicle *)car->CEntity,
                true, (M2::E_VehicleSeat)ped->seat, false
            );

            ped->target_entityid = M2O_INVALID_ENTITY;
        }
    }
}

/**
 * The entity in our stream zone gets updated
 */
void module_ped_callback_update(librg_event_t *event) {
    auto entity = event->entity; mod_assert(entity);
    auto ped = get_ped(event->entity);

    // skip the udpate if we have removed ped cuz he was inside a removed car
    if (!ped->CEntity) return;

    // make sure we have all objects
    mod_assert(ped && ped->CEntity);
    librg_data_rptr(event->data, &ped->stream, sizeof(ped->stream));

    /* update interpolation tables */
    cubic_hermite_v3_value(&ped->inter_pos, event->entity->position);

    // ped->inter_pos.targ = event->entity->position;
    // ped->inter_pos.last_speed = ped->inter_pos.targ_speed;
    // ped->inter_pos.targ_speed = ped->stream.vspeed;
    // ped->inter_rot.last = ped->inter_rot.targ;
    // ped->inter_rot.targ = ped->stream.rotation;

    // ped->CHuman->GetScript()->ScrLookAt(
    //     &ped->sync, nullptr, ped->stream.look_at, true
    // );

    // // apply movement anim
    // if (ped->stream.state == PED_ON_GROUND) {
    //     auto extr_shift = ped->stream.direction * 13.0f; /* create extrapolated shift for ped */
    //     auto targ_pos = entity->position + extr_shift;

    //     targ_pos.z = entity->position.z;
    //     ped->CHuman->SetDir(vec3(ped->stream.direction.x, ped->stream.direction.y, 0.0f));
    //     // return;

    //     //if (interpolate->step++ > 10) {
    //         interpolate->step = 0;

    //         return;
    //         if (ped->sync) {
    //             ped->sync->Done();
    //         }
    //         ped->CHuman->GetScript()->ScrMoveV(
    //             &ped->sync, targ_pos, (M2::eHumanMoveMode)ped->stream.move_state,
    //             vec3(ped->stream.direction.x, ped->stream.direction.y, 0.0f), true
    //         );
    //     //}
    // } else {
    //     // if we are not on the ground
    //     // our prev position will be always our current
    //     // so that after we appear on the ground again
    //     // we won't be interpolated from somewhere far away
    //     interpolate->last_position = entity->position;
    // }

    ped->inter_delta = 0.0f;

    module_ped_tasks_update(ped);
}

#define valid_dir(x) (zplm_abs(x) > 0.0f && zplm_abs(x) < 1.0f)

/**
 * The entity is streamed by us, and we are sending an update with new data
 */
void module_ped_callback_clientstream(librg_event_t *event) {
    auto entity = event->entity; mod_assert(entity);
    auto ped = get_ped(event->entity);

    // constnaly set our health to top (DEBUG)
    ped->CHuman->GetScript()->SetHealth(720.0f);

    // make sure we have all objects
    mod_assert(ped && ped->CEntity);

    // TODO: add checks for being on the ground

    // read new values of entity
    auto new_position   = ped->CEntity->GetPosition();
    auto diff_position  = new_position - entity->position;

    entity->position    = new_position;
    ped->stream.vspeed = diff_position;

    // if (event->entity->id != mod.player->id) {
    //     // lower limits
    //     // 0.05 - 0.06 - walking
    //     // 0.13 - 0.14 - running
    //     // 0.19 - 0.20 - sprinting
    //     f32 ped_speed = zplm_vec3_mag(diff_position);

    //     /**/ if (ped_speed > 0.19f) {
    //         ped->stream.move_state = (u8)M2::HUMAN_MOVE_MODE_SPRINT;
    //     }
    //     else if (ped_speed > 0.13f) {
    //         ped->stream.move_state = (u8)M2::HUMAN_MOVE_MODE_RUN;
    //     }
    //     else if (ped_speed > 0.01f) {
    //         ped->stream.move_state = (u8)M2::HUMAN_MOVE_MODE_WALK;
    //     }
    //     else {
    //         ped->stream.move_state = (u8)M2::HUMAN_MOVE_MODE_BREATH;
    //     }
    // }
    // else {
    //     auto movestate = ped->CPlayer->m_pPlayerControls.m_ePlayerMovementState;

    //     // convert local player movement to human movement
    //     switch (movestate) {
    //         case M2::E_MOVEMENT_WALK:     ped->stream.move_state = M2::HUMAN_MOVE_MODE_WALK; break;
    //         case M2::E_MOVEMENT_JOG:      ped->stream.move_state = M2::HUMAN_MOVE_MODE_RUN; break;
    //         case M2::E_MOVEMENT_SPRINT:   ped->stream.move_state = M2::HUMAN_MOVE_MODE_SPRINT; break;
    //         case M2::E_MOVEMENT_IDLE:     ped->stream.move_state = M2::HUMAN_MOVE_MODE_BREATH; break;
    //         case M2::E_MOVEMENT_STOPPING: ped->stream.move_state = M2::HUMAN_MOVE_MODE_END; break;
    //     }
    // }

    // f32 ped_speed = zplm_vec3_mag(diff_position);
    // ped->stream.is_accelerating = (ped_speed > ped->stream.speed);
    // ped->stream.speed = ped_speed;

    // assign and send new values
    // vec3_t newdir; zplm_vec3_norm0(&newdir, diff_position);
    // if ((valid_dir(newdir.x) || valid_dir(newdir.y)) && ped->stream.is_accelerating) {
    //     ped->stream.direction = (ped->stream.direction * 3.0 + newdir) / 4.f; // calc average
    // }

    librg_data_wptr(event->data, &ped->stream, sizeof(ped->stream));
}

// =======================================================================//
// !
// ! Interpolation
// !
// =======================================================================//

void module_ped_callback_interpolate(librg_entity_t *entity) {
    auto ped = get_ped(entity);

    // skip the udpate if we have removed ped cuz he was inside a removed car
    if (!ped->CEntity) return;

    // last delta tick against constant tick delay
    f32 alpha = ped->inter_delta / ctx->timesync.server_delay;
    ped->inter_delta += (f32)mod.last_delta;

    if (ped->stream.state != PED_ON_GROUND) {
        return;
    }

    ped->CHuman->SetPos(cubic_hermite_v3_interpolate(&ped->inter_pos, alpha));
}

// =======================================================================//
// !
// ! Custom events
// !
// =======================================================================//

void module_ped_init() {

}

void mod_player_spawn() {
    auto ped = get_ped(mod.player);

    M2::C_GfxEnvironmentEffects::Get()->GetWeatherManager()->SetTime(0.5); /* 0.0 .. 1.0 - time of the day */

   /* if (M2::C_SDSLoadingTable::Get()) {
        M2::C_SDSLoadingTable::Get()->ActivateStreamMapLine("free_joe_load");
        M2::C_SDSLoadingTable::Get()->ActivateStreamMapLine("free_summer_load");

        M2::C_GfxEnvironmentEffects::Get()->GetWeatherManager()->SetDayTemplate("DT_RTRclear_day_late_afternoon");
        mod_log("[info] setting day template: %s\n", "DT_RTRclear_day_late_afternoon");
    }*/

    /* Disable ambiant peds */
    M2::Wrappers::SwitchFarAmbiants(false);
    M2::Wrappers::SwitchGenerators(false);

    /* Lock to prevent actions while respawning */
    ped->CPlayer->LockControls(true);

    /* Resetting player */
    ped->CHuman->GetScript()->SetHealth(720.0f);
    ped->CEntity->SetPosition(vec3f(-421.75f, 479.31f, 0.05f));

    /* Enabling controls */
    ped->CPlayer->LockControls(false);
}