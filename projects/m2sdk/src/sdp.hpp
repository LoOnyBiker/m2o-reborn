/**
 * @file SteamDRMPatcher
 * @brief I hate steam.
 * @author MyU (myudev0@gmail.com)
 */

DWORD _sdp_jmp[] = {
    0x41a5a3 + 0xA,
    0x42dae7 + 0xA,
    0x46d597 + 0xA,
    0x46e257 + 0xA,
    0x4723a7 + 0xA,
    0x473504 + 0xA,
    0x473ca7 + 0xA,
    0x4751b7 + 0xA,
    0x475a87 + 0xA,
    0x475d17 + 0xA,
    0x475f67 + 0xA,
    0x476107 + 0xA,
    0x4767d3 + 0xA,
    0x476853 + 0xA,
    0x476f33 + 0xA,
    0x477b77 + 0xA,
    0x477f67 + 0xA,
    0x478327 + 0xA,
    0x478447 + 0xA,
    0x478bb3 + 0xA,
    0x488617 + 0xA,
    0x489837 + 0xA,
    0x48b397 + 0xA,
    0x48b627 + 0xA,
    0x49b56b + 0xA,
    0x49ce5b + 0xA,
    0x49d1d7 + 0xA,
    0x49dbb7 + 0xA,
    0x49f727 + 0xA,
    0x4a7a97 + 0xA,
    0x4a8c97 + 0xA,
    0x4a9c87 + 0xA,
    0x4adef7 + 0xA,
    0x4ae347 + 0xA,
    0x4af177 + 0xA,
    0x4b3157 + 0xA,
    0x4c1d9b + 0xA,
    0x4c261f + 0xA,
    0x4cd0e7 + 0xA,
    0x4d7537 + 0xA,
    0x4de712 + 0xA,
    0x4e4478 + 0xA,
    0x4eda07 + 0xA,
    0x4ee007 + 0xA,
    0x4ee2a3 + 0xA,
    0x4f1878 + 0xA,
    0x4f2af7 + 0xA,
    0x4f35e7 + 0xA,
    0x4f8347 + 0xA,
    0x4fbb17 + 0xA,
    0x4fd597 + 0xA,
    0x5018c3 + 0xA,
    0x5036c7 + 0xA
};

DWORD _sdp_stf[] = {
    0xdd85f0,
    0xdd8820,
    0xdd8a50,
    0xdd8c90,
    0xdd8ec0,
    0xdd9100,
    0xdd9330,
    0xdd9570,
    0xdd97a0,
    0xdd99e0,
    0xdd9c40,
    0xdd9ed0,
    0xdda130,
    0xdda3c0,
    0xdda620,
    0xdda8c0,
    0xddab20,
    0xddadc0,
    0xddb020,
    0xddb2c0,
    0xddb4f0,
    0xddb740,
    0xddb970,
    0xddbbc0,
    0xddbdf0,
    0xddc040,
    0xddc270,
    0xddc4c0,
    0xddc6f0,
    0xddc940,
    0xddcba0,
    0xddce40,
    0xddd0a0,
    0xddd340,
    0xddd5a0,
    0xddd840,
    0xdddaa0,
    0xdddd40,
    0xdddfa0,
    0xdde240,
    0xdde470,
    0xdde6c0,
    0xdde8f0,
    0xddeb40,
    0xdded70,
    0xddefc0,
    0xddf1f0,
    0xddf440,
    0xddf670,
    0xddf8c0,
    0xddfaf0,
    0xddfd40,
    0xddff70,
    0xde01c0,
    0xde03f0,
    0xde0640,
    0xde0870,
    0xde0ac0,
    0xde0cf0,
    0xde0f40,
    0xde1170,
    0xde13d0,
    0xde1600,
    0xde1860,
    0xde1a90,
    0xde1cf0,
    0xde1f20,
    0xde2180,
    0xde23b0,
    0xde2610,
    0xde2800,
    0xde2a10,
    0xde2c00,
    0xde2e10,
    0xde3000,
    0xde3210,
    0xde3400,
    0xde3610,
    0xde3800,
    0xde3a10,
    0xde3c00,
    0xde3e10,
    0xde4000,
    0xde4210,
    0xde4400,
    0xde4610,
    0xde4800,
    0xde4a10,
    0xde4c00,
    0xde4e10,
    0xde5000,
    0xde5210,
    0xde5400,
    0xde5610,
    0xde5860,
    0xde5a90,
    0xde5cc0,
    0xde5ef0,
    0xde6120,
    0xde6380,
    0xde65e0,
    0xde6840,
    0xde6aa0,
    0xde6d00,
    0xde6f30,
    0xde7160,
    0xde7390,
    0xde75c0,
    0xde77f0,
    0xde7a50,
    0xde7cb0,
    0xde7f10,
    0xde8170,
    0xde83d0,
    0xde8600,
    0xde8830,
    0xde8a60,
    0xde8c90,
    0xde8ec0,
    0xde90f0,
    0xde9320,
    0xde9550,
    0xde9780,
    0xde99b0,
    0xde9be0,
    0xde9e10,
    0xdea040,
    0xdea270,
    0xdea4a0,
    0xdea690,
    0xdea880,
    0xdeaa70,
    0xdeac60,
    0xdeae50,
    0xdeb040,
    0xdeb230,
    0xdeb420,
    0xdeb610,
    0xdeb800,
    0xdeb9f0,
    0xdebbe0,
    0xdebdd0
};

DWORD _sdp_stf2[] = {
    0x41a450,
    0x420080,
    0x448500,
    0x448900,
    0x4491f0,
    0x449250,
    0x449410,
    0x44a8f0,
    0x44b460,
    0x44c160,
    0x44c310,
    0x44cba0,
    0x44d420,
    0x44d7d0,
    0x44ddb0,
    0x44dee0,
    0x44df60,
    0x44ef10,
    0x44f370,
    0x44ff70,
    0x450650,
    0x450c10,
    0x450fd0,
    0x451090,
    0x4512a0,
    0x451900,
    0x451e90,
    0x451f50,
    0x452130,
    0x452190,
    0x452550,
    0x452940,
    0x452cd0,
    0x452e30,
    0x453190,
    0x4532b0,
    0x4538f0,
    0x453960,
    0x453db0,
    0x453e10,
    0x453ef0,
    0x454190,
    0x454210,
    0x455010,
    0x455770,
    0x455c00,
    0x455d70,
    0x4565c0,
    0x4566d0,
    0x456910,
    0x456a70,
    0x456b00,
    0x456b60,
    0x456c70,
    0x456d50,
    0x456df0
};
struct twoaddrs { DWORD d1, d2; };
twoaddrs _sdp_gen[] = {
    { 0xdd83d0, 0xb3ed14b5 },
    { 0xdd8600, 0x9d613e7f },
    { 0xdd8830, 0xf5da4a8d },
    { 0xdd8a60, 0x871ad839 },
    { 0xdd8ca0, 0x4f9303f5 },
    { 0xdd8ed0, 0x2ea409be },
    { 0xdd9110, 0xdd0b2571 },
    { 0xdd9340, 0x429201fe },
    { 0xdd9580, 0x8f94f525 },
    { 0xdd97b0, 0xcd15e0b4 },
    { 0xdd99f0, 0xd3560558 },
    { 0xdd9c50, 0xf9cae76d },
    { 0xdd9ee0, 0xd033f9db },
    { 0xdda140, 0xaedd84be },
    { 0xdda3d0, 0x565318ec },
    { 0xdda630, 0x3077c2d6 },
    { 0xdda8d0, 0x565318ec },
    { 0xddab30, 0x5bd17017 },
    { 0xddadd0, 0x565318ec },
    { 0xddb030, 0x5fc1b588 },
    { 0xddb2d0, 0xca2f27d0 },
    { 0xddb500, 0xdc04e787 },
    { 0xddb750, 0xb3062fb7 },
    { 0xddb980, 0xd9f517ac },
    { 0xddbbd0, 0x52921c80 },
    { 0xddbe00, 0x52f057ad },
    { 0xddc050, 0x6ede3a12 },
    { 0xddc280, 0x62f39873 },
    { 0xddc4d0, 0xad7474a3 },
    { 0xddc700, 0xe257520f },
    { 0xddc950, 0x565318ec },
    { 0xddcbb0, 0xd372704b },
    { 0xddce50, 0x565318ec },
    { 0xddd0b0, 0x4ffaf7f7 },
    { 0xddd350, 0x565318ec },
    { 0xddd5b0, 0xfba85277 },
    { 0xddd850, 0x565318ec },
    { 0xdddab0, 0x695524ee },
    { 0xdddd50, 0x565318ec },
    { 0xdddfb0, 0x759c1d63 },
    { 0xdde250, 0xe4657b34 },
    { 0xdde480, 0x8788b67b },
    { 0xdde6d0, 0x2ead9da1 },
    { 0xdde900, 0xabad681 },
    { 0xddeb50, 0xabe2a41 },
    { 0xdded80, 0x5923a780 },
    { 0xddefd0, 0xe015d439 },
    { 0xddf200, 0xfbac5848 },
    { 0xddf450, 0x8037487 },
    { 0xddf680, 0x1fef1717 },
    { 0xddf8d0, 0xec403bd8 },
    { 0xddfb00, 0xf47d63c7 },
    { 0xddfd50, 0x7d24f08 },
    { 0xddff80, 0x8ed70c8b },
    { 0xde01d0, 0x7d782044 },
    { 0xde0400, 0x66c1ac35 },
    { 0xde0650, 0x9c74799e },
    { 0xde0880, 0x8282e36a },
    { 0xde0ad0, 0x76246779 },
    { 0xde0d00, 0x691097ba },
    { 0xde0f50, 0x575618ec },
    { 0xde1180, 0xc16c2c0a },
    { 0xde13e0, 0x575618ec },
    { 0xde1610, 0xd04b8d71 },
    { 0xde1870, 0x575618ec },
    { 0xde1aa0, 0x6a02c409 },
    { 0xde1d00, 0x575618ec },
    { 0xde1f30, 0x2d8e1256 },
    { 0xde2190, 0x575618ec },
    { 0xde23c0, 0x9581e577 },
    { 0xde2620, 0xcf069fe2 },
    { 0xde2810, 0x9c9b1c13 },
    { 0xde2a20, 0xc80f373e },
    { 0xde2c10, 0x9b92b4cf },
    { 0xde2e20, 0xdd336d2a },
    { 0xde3010, 0x8eaeeedb },
    { 0xde3220, 0xda3ac5f6 },
    { 0xde3410, 0x89a74607 },
    { 0xde3620, 0xd3203c92 },
    { 0xde3810, 0x80bdbf63 },
    { 0xde3a20, 0xd429944e },
    { 0xde3c10, 0x87b417bf },
    { 0xde3e20, 0x89c2057a },
    { 0xde4010, 0xda5f868b },
    { 0xde4220, 0x8ecbada6 },
    { 0xde4410, 0xdd562e57 },
    { 0xde4620, 0x87d154c2 },
    { 0xde4810, 0xd44cd733 },
    { 0xde4a20, 0x80d8fc1e },
    { 0xde4c10, 0xd3457fef },
    { 0xde4e20, 0x95e4a60a },
    { 0xde5010, 0xc67925fb },
    { 0xde5220, 0x92ed0ed6 },
    { 0xde5410, 0xc1708d27 },
    { 0xde5640, 0xa0d100b1 },
    { 0xde5870, 0x2533c278 },
    { 0xde5aa0, 0xeab3b168 },
    { 0xde5cd0, 0x191c9da7 },
    { 0xde5f00, 0x107f8693 },
    { 0xde6130, 0x39ba2594 },
    { 0xde6390, 0xd47b73b2 },
    { 0xde65f0, 0x5d2ac177 },
    { 0xde6850, 0x565318ec },
    { 0xde6ab0, 0x565318ec },
    { 0xde6d10, 0x38883fc3 },
    { 0xde6f40, 0xc10d3998 },
    { 0xde7170, 0x2a017d55 },
    { 0xde73a0, 0xef1a513f },
    { 0xde75d0, 0x338f7f9d },
    { 0xde7800, 0x565318ec },
    { 0xde7a60, 0x565318ec },
    { 0xde7cc0, 0x565318ec },
    { 0xde7f20, 0x565318ec },
    { 0xde8180, 0x565318ec },
    { 0xde83e0, 0xbd7c9793 },
    { 0xde8610, 0x51e420ff },
    { 0xde8840, 0x9de64541 },
    { 0xde8a70, 0xac378bfa },
    { 0xde8ca0, 0x64be5036 },
    { 0xde8ed0, 0x822d26ed },
    { 0xde9100, 0xa63f212d },
    { 0xde9330, 0xc98dfd03 },
    { 0xde9560, 0xec5d90f4 },
    { 0xde9790, 0x16e8455f },
    { 0xde99c0, 0x575618ec },
    { 0xde9bf0, 0x575618ec },
    { 0xde9e20, 0x575618ec },
    { 0xdea050, 0x575618ec },
    { 0xdea280, 0x575618ec },
    { 0xdea4b0, 0x99ed48cc },
    { 0xdea6a0, 0xc36a3259 },
    { 0xdea890, 0x4688f090 },
    { 0xdeaa80, 0x121cdbbd },
    { 0xdeac70, 0xe1b3f772 },
    { 0xdeae60, 0xa7122e97 },
    { 0xdeb050, 0xcfa95a65 },
    { 0xdeb240, 0x9b3d7148 },
    { 0xdeb430, 0x68925d87 },
    { 0xdeb620, 0x32152712 },
    { 0xdeb810, 0xb5b15b82 },
    { 0xdeba00, 0xe62cd873 },
    { 0xdebbf0, 0x128a5c60 }
};

twoaddrs _sdp_jmp2[] = {
    { 0x41a450, 0x12b },
    { 0x420080, 0xda3b },
    { 0x448500, 0x400eb },
    { 0x448900, 0x24c6b },
    { 0x4491f0, 0x954eb },
    { 0x449250, 0x24fdb },
    { 0x449410, 0x403fb },
    { 0x44a8f0, 0x5d17b },
    { 0x44b460, 0xa63eb },
    { 0x44c160, 0x3f20b },
    { 0x44c310, 0x3f2eb },
    { 0x44cba0, 0x4e99b },
    { 0x44d420, 0x60aab },
    { 0x44d7d0, 0x24bab },
    { 0x44ddb0, 0xb3aeb },
    { 0x44dee0, 0xb57bb },
    { 0x44df60, 0x73e0b },
    { 0x44ef10, 0x6421b },
    { 0x44f370, 0x5efab },
    { 0x44ff70, 0xa2b5b },
    { 0x450650, 0x22e8b },
    { 0x450c10, 0x2306b },
    { 0x450fd0, 0x4be5b },
    { 0x451090, 0xa728b },
    { 0x4512a0, 0x4bf0b },
    { 0x451900, 0x9c0db },
    { 0x451e90, 0x5d2bb },
    { 0x451f50, 0xacc2b },
    { 0x452130, 0x9231b },
    { 0x452190, 0x22ffb },
    { 0x452550, 0x4b63b },
    { 0x452940, 0x2311b },
    { 0x452cd0, 0x9b30b },
    { 0x452e30, 0x22ebb },
    { 0x453190, 0x6f45b },
    { 0x4532b0, 0x22c8b },
    { 0x4538f0, 0x227eb },
    { 0x453960, 0xa9c0b },
    { 0x453db0, 0x229fb },
    { 0x453e10, 0x9a46b },
    { 0x453ef0, 0x2293b },
    { 0x454190, 0x22d7b },
    { 0x454210, 0x78eab },
    { 0x455010, 0x22b3b },
    { 0x455770, 0x227cb },
    { 0x455c00, 0x226fb },
    { 0x455d70, 0x226ab },
    { 0x4565c0, 0x5369b },
    { 0x4566d0, 0x80e3b },
    { 0x456910, 0x2227b },
    { 0x456a70, 0x48c8b },
    { 0x456b00, 0x58b0b },
    { 0x456b60, 0xa4f8b },
    { 0x456c70, 0x9c94b },
    { 0x456d50, 0x5d8db },
    { 0x456df0, 0x5da0b }
};

void sdp_install()
{
    for (auto patchaddr : _sdp_jmp)
    {
        Mem::ScopedProtect(patchaddr, 1);
        if (*(BYTE*)(patchaddr) == 0x74)
        {
            *(BYTE*)(patchaddr) = 0xEB;
        }
    }

    for (auto& genent : _sdp_gen)
    {
        if (*(BYTE*)(genent.d1) == 0x81)
        {
            Mem::ScopedProtect(genent.d1, 7);
            *(BYTE*)(genent.d1) = 0xB8;
            *(DWORD*)(genent.d1 + 1) = genent.d2;
            *(BYTE*)(genent.d1 + 6) = 0xC3;
        }
    }

    for (auto& jmpent : _sdp_jmp2)
    {
        if (*(BYTE*)(jmpent.d1) == 0x51)
        {
            Mem::ScopedProtect(jmpent.d1, 11);
            Mem::Utilites::InstallNopPatch(jmpent.d1, 11);

            *(BYTE*)(jmpent.d1) = 0xE9;
            *(DWORD*)(jmpent.d1 + 1) = jmpent.d2;
        }
    }
}
