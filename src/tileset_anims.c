// Includes
#include "global.h"
#include "palette.h"
#include "util.h"
#include "battle_transition.h"
#include "task.h"
#include "battle_transition.h"
#include "fieldmap.h"

// Static type declarations

// Static RAM declarations

static EWRAM_DATA struct {
    const u16 *src;
    u16 *dest;
    u16 size;
} sTilesetDMA3TransferBuffer[20] = {0};

static u8 sTilesetDMA3TransferBufferSize;
static u16 sPrimaryTilesetCBCounter;
static u16 sPrimaryTilesetCBBufferSize;
static u16 sSecondaryTilesetCBCounter;
static u16 sSecondaryTilesetCBBufferSize;
static void (*sPrimaryTilesetCB)(u16);
static void (*sSecondaryTilesetCB)(u16);

// Static ROM declarations

static void cur_mapheader_run_tileset1_func(void);
static void cur_mapheader_run_tileset2_func(void);

// .rodata


const u16 gTilesetAnims_General0_Frame1[] = INCBIN_U16("data/tilesets/primary/general/anim/0/1.4bpp");

const u16 gTilesetAnims_General0_Frame0[] = INCBIN_U16("data/tilesets/primary/general/anim/0/0.4bpp");

const u16 gTilesetAnims_General0_Frame2[] = INCBIN_U16("data/tilesets/primary/general/anim/0/2.4bpp");

const u16 tileset_anims_space_0[16] = {};

const u16 *const gTilesetAnims_General0[] = {
    gTilesetAnims_General0_Frame0,
    gTilesetAnims_General0_Frame1,
    gTilesetAnims_General0_Frame0,
    gTilesetAnims_General0_Frame2
};

const u16 gTilesetAnims_General1_Frame0[] = INCBIN_U16("data/tilesets/primary/general/anim/1/0.4bpp");

const u16 gTilesetAnims_General1_Frame1[] = INCBIN_U16("data/tilesets/primary/general/anim/1/1.4bpp");

const u16 gTilesetAnims_General1_Frame2[] = INCBIN_U16("data/tilesets/primary/general/anim/1/2.4bpp");

const u16 gTilesetAnims_General1_Frame3[] = INCBIN_U16("data/tilesets/primary/general/anim/1/3.4bpp");

const u16 gTilesetAnims_General1_Frame4[] = INCBIN_U16("data/tilesets/primary/general/anim/1/4.4bpp");

const u16 gTilesetAnims_General1_Frame5[] = INCBIN_U16("data/tilesets/primary/general/anim/1/5.4bpp");

const u16 gTilesetAnims_General1_Frame6[] = INCBIN_U16("data/tilesets/primary/general/anim/1/6.4bpp");

const u16 gTilesetAnims_General1_Frame7[] = INCBIN_U16("data/tilesets/primary/general/anim/1/7.4bpp");

const u16 *const gTilesetAnims_General1[] = {
    gTilesetAnims_General1_Frame0,
    gTilesetAnims_General1_Frame1,
    gTilesetAnims_General1_Frame2,
    gTilesetAnims_General1_Frame3,
    gTilesetAnims_General1_Frame4,
    gTilesetAnims_General1_Frame5,
    gTilesetAnims_General1_Frame6,
    gTilesetAnims_General1_Frame7
};

const u16 gTilesetAnims_General2_Frame0[] = INCBIN_U16("data/tilesets/primary/general/anim/2/0.4bpp");

const u16 gTilesetAnims_General2_Frame1[] = INCBIN_U16("data/tilesets/primary/general/anim/2/1.4bpp");

const u16 gTilesetAnims_General2_Frame2[] = INCBIN_U16("data/tilesets/primary/general/anim/2/2.4bpp");

const u16 gTilesetAnims_General2_Frame3[] = INCBIN_U16("data/tilesets/primary/general/anim/2/3.4bpp");

const u16 gTilesetAnims_General2_Frame4[] = INCBIN_U16("data/tilesets/primary/general/anim/2/4.4bpp");

const u16 gTilesetAnims_General2_Frame5[] = INCBIN_U16("data/tilesets/primary/general/anim/2/5.4bpp");

const u16 gTilesetAnims_General2_Frame6[] = INCBIN_U16("data/tilesets/primary/general/anim/2/6.4bpp");

const u16 *const gTilesetAnims_General2[] = {
    gTilesetAnims_General2_Frame0,
    gTilesetAnims_General2_Frame1,
    gTilesetAnims_General2_Frame2,
    gTilesetAnims_General2_Frame3,
    gTilesetAnims_General2_Frame4,
    gTilesetAnims_General2_Frame5,
    gTilesetAnims_General2_Frame6,
    gTilesetAnims_General2_Frame0
};

const u16 gTilesetAnims_General3_Frame0[] = INCBIN_U16("data/tilesets/primary/general/anim/3/0.4bpp");

const u16 gTilesetAnims_General3_Frame1[] = INCBIN_U16("data/tilesets/primary/general/anim/3/1.4bpp");

const u16 gTilesetAnims_General3_Frame2[] = INCBIN_U16("data/tilesets/primary/general/anim/3/2.4bpp");

const u16 gTilesetAnims_General3_Frame3[] = INCBIN_U16("data/tilesets/primary/general/anim/3/3.4bpp");

const u16 *const gTilesetAnims_General3[] = {
    gTilesetAnims_General3_Frame0,
    gTilesetAnims_General3_Frame1,
    gTilesetAnims_General3_Frame2,
    gTilesetAnims_General3_Frame3
};

const u16 gTilesetAnims_General4_Frame0[] = INCBIN_U16("data/tilesets/primary/general/anim/4/0.4bpp");

const u16 gTilesetAnims_General4_Frame1[] = INCBIN_U16("data/tilesets/primary/general/anim/4/1.4bpp");

const u16 gTilesetAnims_General4_Frame2[] = INCBIN_U16("data/tilesets/primary/general/anim/4/2.4bpp");

const u16 gTilesetAnims_General4_Frame3[] = INCBIN_U16("data/tilesets/primary/general/anim/4/3.4bpp");

const u16 *const gTilesetAnims_General4[] = {
    gTilesetAnims_General4_Frame0,
    gTilesetAnims_General4_Frame1,
    gTilesetAnims_General4_Frame2,
    gTilesetAnims_General4_Frame3
};

const u16 gTilesetAnims_Lavaridge0_Frame0[] = INCBIN_U16("data/tilesets/secondary/lavaridge/anim/0.4bpp");

const u16 gTilesetAnims_Lavaridge0_Frame1[] = INCBIN_U16("data/tilesets/secondary/lavaridge/anim/1.4bpp");

const u16 gTilesetAnims_Lavaridge0_Frame2[] = INCBIN_U16("data/tilesets/secondary/lavaridge/anim/2.4bpp");

const u16 gTilesetAnims_Lavaridge0_Frame3[] = INCBIN_U16("data/tilesets/secondary/lavaridge/anim/3.4bpp");

const u16 *const gTilesetAnims_Lavaridge0[] = {
    gTilesetAnims_Lavaridge0_Frame0,
    gTilesetAnims_Lavaridge0_Frame1,
    gTilesetAnims_Lavaridge0_Frame2,
    gTilesetAnims_Lavaridge0_Frame3
};

const u16 gTilesetAnims_Pacifidlog0_Frame0[] = INCBIN_U16("data/tilesets/secondary/pacifidlog/anim/0/0.4bpp");

const u16 gTilesetAnims_Pacifidlog0_Frame1[] = INCBIN_U16("data/tilesets/secondary/pacifidlog/anim/0/1.4bpp");

const u16 gTilesetAnims_Pacifidlog0_Frame2[] = INCBIN_U16("data/tilesets/secondary/pacifidlog/anim/0/2.4bpp");

const u16 *const gTilesetAnims_Pacifidlog0[] = {
    gTilesetAnims_Pacifidlog0_Frame0,
    gTilesetAnims_Pacifidlog0_Frame1,
    gTilesetAnims_Pacifidlog0_Frame2,
    gTilesetAnims_Pacifidlog0_Frame1
};

const u16 gTilesetAnims_Underwater0_Frame0[] = INCBIN_U16("data/tilesets/secondary/underwater/anim/0.4bpp");

const u16 gTilesetAnims_Underwater0_Frame1[] = INCBIN_U16("data/tilesets/secondary/underwater/anim/1.4bpp");

const u16 gTilesetAnims_Underwater0_Frame2[] = INCBIN_U16("data/tilesets/secondary/underwater/anim/2.4bpp");

const u16 gTilesetAnims_Underwater0_Frame3[] = INCBIN_U16("data/tilesets/secondary/underwater/anim/3.4bpp");

const u16 *const gTilesetAnims_Underwater0[] = {
    gTilesetAnims_Underwater0_Frame0,
    gTilesetAnims_Underwater0_Frame1,
    gTilesetAnims_Underwater0_Frame2,
    gTilesetAnims_Underwater0_Frame3
};

const u16 gTilesetAnims_Pacifidlog1_Frame0[] = INCBIN_U16("data/tilesets/secondary/pacifidlog/anim/1/0.4bpp");

const u16 gTilesetAnims_Pacifidlog1_Frame1[] = INCBIN_U16("data/tilesets/secondary/pacifidlog/anim/1/1.4bpp");

const u16 gTilesetAnims_Pacifidlog1_Frame2[] = INCBIN_U16("data/tilesets/secondary/pacifidlog/anim/1/2.4bpp");

const u16 gTilesetAnims_Pacifidlog1_Frame3[] = INCBIN_U16("data/tilesets/secondary/pacifidlog/anim/1/3.4bpp");

const u16 gTilesetAnims_Pacifidlog1_Frame4[] = INCBIN_U16("data/tilesets/secondary/pacifidlog/anim/1/4.4bpp");

const u16 gTilesetAnims_Pacifidlog1_Frame5[] = INCBIN_U16("data/tilesets/secondary/pacifidlog/anim/1/5.4bpp");

const u16 gTilesetAnims_Pacifidlog1_Frame6[] = INCBIN_U16("data/tilesets/secondary/pacifidlog/anim/1/6.4bpp");

const u16 gTilesetAnims_Pacifidlog1_Frame7[] = INCBIN_U16("data/tilesets/secondary/pacifidlog/anim/1/7.4bpp");

const u16 *const gTilesetAnims_Pacifidlog1[] = {
    gTilesetAnims_Pacifidlog1_Frame0,
    gTilesetAnims_Pacifidlog1_Frame1,
    gTilesetAnims_Pacifidlog1_Frame2,
    gTilesetAnims_Pacifidlog1_Frame3,
    gTilesetAnims_Pacifidlog1_Frame4,
    gTilesetAnims_Pacifidlog1_Frame5,
    gTilesetAnims_Pacifidlog1_Frame6,
    gTilesetAnims_Pacifidlog1_Frame7
};

const u16 gTilesetAnims_Mauville0a_Frame0[] = INCBIN_U16("data/tilesets/secondary/mauville/anim/0/a/0.4bpp");

const u16 gTilesetAnims_Mauville0a_Frame1[] = INCBIN_U16("data/tilesets/secondary/mauville/anim/0/a/1.4bpp");

const u16 gTilesetAnims_Mauville0a_Frame2[] = INCBIN_U16("data/tilesets/secondary/mauville/anim/0/a/2.4bpp");

const u16 gTilesetAnims_Mauville0a_Frame3[] = INCBIN_U16("data/tilesets/secondary/mauville/anim/0/a/3.4bpp");

const u16 gTilesetAnims_Mauville1a_Frame1[] = INCBIN_U16("data/tilesets/secondary/mauville/anim/1/a/1.4bpp");

const u16 gTilesetAnims_Mauville0b_Frame0[] = INCBIN_U16("data/tilesets/secondary/mauville/anim/0/b/0.4bpp");

const u16 gTilesetAnims_Mauville0b_Frame1[] = INCBIN_U16("data/tilesets/secondary/mauville/anim/0/b/1.4bpp");

const u16 gTilesetAnims_Mauville0b_Frame2[] = INCBIN_U16("data/tilesets/secondary/mauville/anim/0/b/2.4bpp");

const u16 gTilesetAnims_Mauville0b_Frame3[] = INCBIN_U16("data/tilesets/secondary/mauville/anim/0/b/3.4bpp");

const u16 gTilesetAnims_Mauville1b_Frame1[] = INCBIN_U16("data/tilesets/secondary/mauville/anim/1/b/1.4bpp");

const u16 tileset_anims_space_1[16] = {};

u16 *const gTilesetAnims_MauvilleVDests0[] = {
    (u16 *)(BG_VRAM + TILE_OFFSET_4BPP(NUM_TILES_IN_PRIMARY + 96)),
    (u16 *)(BG_VRAM + TILE_OFFSET_4BPP(NUM_TILES_IN_PRIMARY + 100)),
    (u16 *)(BG_VRAM + TILE_OFFSET_4BPP(NUM_TILES_IN_PRIMARY + 104)),
    (u16 *)(BG_VRAM + TILE_OFFSET_4BPP(NUM_TILES_IN_PRIMARY + 108)),
    (u16 *)(BG_VRAM + TILE_OFFSET_4BPP(NUM_TILES_IN_PRIMARY + 112)),
    (u16 *)(BG_VRAM + TILE_OFFSET_4BPP(NUM_TILES_IN_PRIMARY + 116)),
    (u16 *)(BG_VRAM + TILE_OFFSET_4BPP(NUM_TILES_IN_PRIMARY + 120)),
    (u16 *)(BG_VRAM + TILE_OFFSET_4BPP(NUM_TILES_IN_PRIMARY + 124))
};

u16 *const gTilesetAnims_MauvilleVDests1[] = {
    (u16 *)(BG_VRAM + TILE_OFFSET_4BPP(NUM_TILES_IN_PRIMARY + 128)),
    (u16 *)(BG_VRAM + TILE_OFFSET_4BPP(NUM_TILES_IN_PRIMARY + 132)),
    (u16 *)(BG_VRAM + TILE_OFFSET_4BPP(NUM_TILES_IN_PRIMARY + 136)),
    (u16 *)(BG_VRAM + TILE_OFFSET_4BPP(NUM_TILES_IN_PRIMARY + 140)),
    (u16 *)(BG_VRAM + TILE_OFFSET_4BPP(NUM_TILES_IN_PRIMARY + 144)),
    (u16 *)(BG_VRAM + TILE_OFFSET_4BPP(NUM_TILES_IN_PRIMARY + 148)),
    (u16 *)(BG_VRAM + TILE_OFFSET_4BPP(NUM_TILES_IN_PRIMARY + 152)),
    (u16 *)(BG_VRAM + TILE_OFFSET_4BPP(NUM_TILES_IN_PRIMARY + 156))
};

const u16 *const gTilesetAnims_Mauville0a[] = {
    gTilesetAnims_Mauville0a_Frame0,
    gTilesetAnims_Mauville0a_Frame0,
    gTilesetAnims_Mauville0a_Frame1,
    gTilesetAnims_Mauville0a_Frame2,
    gTilesetAnims_Mauville0a_Frame3,
    gTilesetAnims_Mauville0a_Frame3,
    gTilesetAnims_Mauville0a_Frame3,
    gTilesetAnims_Mauville0a_Frame3,
    gTilesetAnims_Mauville0a_Frame3,
    gTilesetAnims_Mauville0a_Frame3,
    gTilesetAnims_Mauville0a_Frame2,
    gTilesetAnims_Mauville0a_Frame1
};

const u16 *const gTilesetAnims_Mauville0b[] = {
    gTilesetAnims_Mauville0b_Frame0,
    gTilesetAnims_Mauville0b_Frame0,
    gTilesetAnims_Mauville0b_Frame1,
    gTilesetAnims_Mauville0b_Frame2,
    gTilesetAnims_Mauville0b_Frame3,
    gTilesetAnims_Mauville0b_Frame3,
    gTilesetAnims_Mauville0b_Frame3,
    gTilesetAnims_Mauville0b_Frame3,
    gTilesetAnims_Mauville0b_Frame3,
    gTilesetAnims_Mauville0b_Frame3,
    gTilesetAnims_Mauville0b_Frame2,
    gTilesetAnims_Mauville0b_Frame1
};

const u16 *const gTilesetAnims_Mauville1a[] = {
    gTilesetAnims_Mauville0a_Frame0,
    gTilesetAnims_Mauville0a_Frame0,
    gTilesetAnims_Mauville1a_Frame1,
    gTilesetAnims_Mauville1a_Frame1
};

const u16 *const gTilesetAnims_Mauville1b[] = {
    gTilesetAnims_Mauville0b_Frame0,
    gTilesetAnims_Mauville0b_Frame0,
    gTilesetAnims_Mauville1b_Frame1,
    gTilesetAnims_Mauville1b_Frame1
};

const u16 gTilesetAnims_Rustboro0_Frame0[] = INCBIN_U16("data/tilesets/secondary/rustboro/anim/0/0.4bpp");

const u16 gTilesetAnims_Rustboro0_Frame1[] = INCBIN_U16("data/tilesets/secondary/rustboro/anim/0/1.4bpp");

const u16 gTilesetAnims_Rustboro0_Frame2[] = INCBIN_U16("data/tilesets/secondary/rustboro/anim/0/2.4bpp");

const u16 gTilesetAnims_Rustboro0_Frame3[] = INCBIN_U16("data/tilesets/secondary/rustboro/anim/0/3.4bpp");

const u16 gTilesetAnims_Rustboro0_Frame4[] = INCBIN_U16("data/tilesets/secondary/rustboro/anim/0/4.4bpp");

const u16 gTilesetAnims_Rustboro0_Frame5[] = INCBIN_U16("data/tilesets/secondary/rustboro/anim/0/5.4bpp");

const u16 gTilesetAnims_Rustboro0_Frame6[] = INCBIN_U16("data/tilesets/secondary/rustboro/anim/0/6.4bpp");

const u16 gTilesetAnims_Rustboro0_Frame7[] = INCBIN_U16("data/tilesets/secondary/rustboro/anim/0/7.4bpp");

u16 *const gTilesetAnims_RustboroVDests0[] = {
    (u16 *)(BG_VRAM + TILE_OFFSET_4BPP(NUM_TILES_IN_PRIMARY + 128)),
    (u16 *)(BG_VRAM + TILE_OFFSET_4BPP(NUM_TILES_IN_PRIMARY + 132)),
    (u16 *)(BG_VRAM + TILE_OFFSET_4BPP(NUM_TILES_IN_PRIMARY + 136)),
    (u16 *)(BG_VRAM + TILE_OFFSET_4BPP(NUM_TILES_IN_PRIMARY + 140)),
    (u16 *)(BG_VRAM + TILE_OFFSET_4BPP(NUM_TILES_IN_PRIMARY + 144)),
    (u16 *)(BG_VRAM + TILE_OFFSET_4BPP(NUM_TILES_IN_PRIMARY + 148)),
    (u16 *)(BG_VRAM + TILE_OFFSET_4BPP(NUM_TILES_IN_PRIMARY + 152)),
    (u16 *)(BG_VRAM + TILE_OFFSET_4BPP(NUM_TILES_IN_PRIMARY + 156))
};

const u16 *const gTilesetAnims_Rustboro0[] = {
    gTilesetAnims_Rustboro0_Frame0,
    gTilesetAnims_Rustboro0_Frame1,
    gTilesetAnims_Rustboro0_Frame2,
    gTilesetAnims_Rustboro0_Frame3,
    gTilesetAnims_Rustboro0_Frame4,
    gTilesetAnims_Rustboro0_Frame5,
    gTilesetAnims_Rustboro0_Frame6,
    gTilesetAnims_Rustboro0_Frame7
};

const u16 gTilesetAnims_Rustboro1_Frame0[] = INCBIN_U16("data/tilesets/secondary/rustboro/anim/1/0.4bpp");

const u16 gTilesetAnims_Rustboro1_Frame1[] = INCBIN_U16("data/tilesets/secondary/rustboro/anim/1/1.4bpp");

const u16 tileset_anims_space_2[16] = {};

const u16 *const gTilesetAnims_Rustboro1[] = {
    gTilesetAnims_Rustboro1_Frame0,
    gTilesetAnims_Rustboro1_Frame1
};

const u16 gTilesetAnims_Lavaridge1_Cave0_Frame0[] = INCBIN_U16("data/tilesets/secondary/cave/anim/0.4bpp");

const u16 gTilesetAnims_Lavaridge1_Cave0_Frame1[] = INCBIN_U16("data/tilesets/secondary/cave/anim/1.4bpp");

const u16 gTilesetAnims_Lavaridge1_Cave0_Frame2[] = INCBIN_U16("data/tilesets/secondary/cave/anim/2.4bpp");

const u16 gTilesetAnims_Lavaridge1_Cave0_Frame3[] = INCBIN_U16("data/tilesets/secondary/cave/anim/3.4bpp");

const u16 gTilesetAnims_Lavaridge1_CaveUnused_Frame0[] = INCBIN_U16("data/tilesets/secondary/cave/anim/unused/0.4bpp");

const u16 gTilesetAnims_Lavaridge1_CaveUnused_Frame1[] = INCBIN_U16("data/tilesets/secondary/cave/anim/unused/1.4bpp");

const u16 gTilesetAnims_Lavaridge1_CaveUnused_Frame2[] = INCBIN_U16("data/tilesets/secondary/cave/anim/unused/2.4bpp");

const u16 gTilesetAnims_Lavaridge1_CaveUnused_Frame3[] = INCBIN_U16("data/tilesets/secondary/cave/anim/unused/3.4bpp");

const u16 tileset_anims_space_3[16] = {};

const u16 *const gTilesetAnims_Lavaridge1_Cave0[] = {
    gTilesetAnims_Lavaridge1_Cave0_Frame0,
    gTilesetAnims_Lavaridge1_Cave0_Frame1,
    gTilesetAnims_Lavaridge1_Cave0_Frame2,
    gTilesetAnims_Lavaridge1_Cave0_Frame3
};

const u16 gTilesetAnims_EverGrande0_Frame0[] = INCBIN_U16("data/tilesets/secondary/ever_grande/anim/0.4bpp");

const u16 gTilesetAnims_EverGrande0_Frame1[] = INCBIN_U16("data/tilesets/secondary/ever_grande/anim/1.4bpp");

const u16 gTilesetAnims_EverGrande0_Frame2[] = INCBIN_U16("data/tilesets/secondary/ever_grande/anim/2.4bpp");

const u16 gTilesetAnims_EverGrande0_Frame3[] = INCBIN_U16("data/tilesets/secondary/ever_grande/anim/3.4bpp");

const u16 gTilesetAnims_EverGrande0_Frame4[] = INCBIN_U16("data/tilesets/secondary/ever_grande/anim/4.4bpp");

const u16 gTilesetAnims_EverGrande0_Frame5[] = INCBIN_U16("data/tilesets/secondary/ever_grande/anim/5.4bpp");

const u16 gTilesetAnims_EverGrande0_Frame6[] = INCBIN_U16("data/tilesets/secondary/ever_grande/anim/6.4bpp");

const u16 gTilesetAnims_EverGrande0_Frame7[] = INCBIN_U16("data/tilesets/secondary/ever_grande/anim/7.4bpp");

const u16 tileset_anims_space_4[16] = {};

u16 *const gTilesetAnims_EverGrandeVDests0[] = {
    (u16 *)(BG_VRAM + TILE_OFFSET_4BPP(NUM_TILES_IN_PRIMARY + 224)),
    (u16 *)(BG_VRAM + TILE_OFFSET_4BPP(NUM_TILES_IN_PRIMARY + 228)),
    (u16 *)(BG_VRAM + TILE_OFFSET_4BPP(NUM_TILES_IN_PRIMARY + 232)),
    (u16 *)(BG_VRAM + TILE_OFFSET_4BPP(NUM_TILES_IN_PRIMARY + 236)),
    (u16 *)(BG_VRAM + TILE_OFFSET_4BPP(NUM_TILES_IN_PRIMARY + 240)),
    (u16 *)(BG_VRAM + TILE_OFFSET_4BPP(NUM_TILES_IN_PRIMARY + 244)),
    (u16 *)(BG_VRAM + TILE_OFFSET_4BPP(NUM_TILES_IN_PRIMARY + 248)),
    (u16 *)(BG_VRAM + TILE_OFFSET_4BPP(NUM_TILES_IN_PRIMARY + 252))
};

const u16 *const gTilesetAnims_EverGrande0[] = {
    gTilesetAnims_EverGrande0_Frame0,
    gTilesetAnims_EverGrande0_Frame1,
    gTilesetAnims_EverGrande0_Frame2,
    gTilesetAnims_EverGrande0_Frame3,
    gTilesetAnims_EverGrande0_Frame4,
    gTilesetAnims_EverGrande0_Frame5,
    gTilesetAnims_EverGrande0_Frame6,
    gTilesetAnims_EverGrande0_Frame7
};

const u16 gTilesetAnims_Dewford0_Frame0[] = INCBIN_U16("data/tilesets/secondary/dewford/anim/0.4bpp");

const u16 gTilesetAnims_Dewford0_Frame1[] = INCBIN_U16("data/tilesets/secondary/dewford/anim/1.4bpp");

const u16 gTilesetAnims_Dewford0_Frame2[] = INCBIN_U16("data/tilesets/secondary/dewford/anim/2.4bpp");

const u16 gTilesetAnims_Dewford0_Frame3[] = INCBIN_U16("data/tilesets/secondary/dewford/anim/3.4bpp");

const u16 *const gTilesetAnims_Dewford0[] = {
    gTilesetAnims_Dewford0_Frame0,
    gTilesetAnims_Dewford0_Frame1,
    gTilesetAnims_Dewford0_Frame2,
    gTilesetAnims_Dewford0_Frame3
};

const u16 gTilesetAnims_BattleFrontierOutsideWest0_Frame0[] = INCBIN_U16("data/tilesets/secondary/battle_frontier_outside_west/anim/0.4bpp");

const u16 gTilesetAnims_BattleFrontierOutsideWest0_Frame1[] = INCBIN_U16("data/tilesets/secondary/battle_frontier_outside_west/anim/1.4bpp");

const u16 gTilesetAnims_BattleFrontierOutsideWest0_Frame2[] = INCBIN_U16("data/tilesets/secondary/battle_frontier_outside_west/anim/2.4bpp");

const u16 gTilesetAnims_BattleFrontierOutsideWest0_Frame3[] = INCBIN_U16("data/tilesets/secondary/battle_frontier_outside_west/anim/3.4bpp");

const u16 *const gTilesetAnims_BattleFrontierOutsideWest0[] = {
    gTilesetAnims_BattleFrontierOutsideWest0_Frame0,
    gTilesetAnims_BattleFrontierOutsideWest0_Frame1,
    gTilesetAnims_BattleFrontierOutsideWest0_Frame2,
    gTilesetAnims_BattleFrontierOutsideWest0_Frame3
};

const u16 gTilesetAnims_BattleFrontierOutsideEast0_Frame0[] = INCBIN_U16("data/tilesets/secondary/battle_frontier_outside_east/anim/0.4bpp");

const u16 gTilesetAnims_BattleFrontierOutsideEast0_Frame1[] = INCBIN_U16("data/tilesets/secondary/battle_frontier_outside_east/anim/1.4bpp");

const u16 gTilesetAnims_BattleFrontierOutsideEast0_Frame2[] = INCBIN_U16("data/tilesets/secondary/battle_frontier_outside_east/anim/2.4bpp");

const u16 gTilesetAnims_BattleFrontierOutsideEast0_Frame3[] = INCBIN_U16("data/tilesets/secondary/battle_frontier_outside_east/anim/3.4bpp");

const u16 *const gTilesetAnims_BattleFrontierOutsideEast0[] = {
    gTilesetAnims_BattleFrontierOutsideEast0_Frame0,
    gTilesetAnims_BattleFrontierOutsideEast0_Frame1,
    gTilesetAnims_BattleFrontierOutsideEast0_Frame2,
    gTilesetAnims_BattleFrontierOutsideEast0_Frame3
};

const u16 gTilesetAnims_Slateport0_Frame0[] = INCBIN_U16("data/tilesets/secondary/slateport/anim/0.4bpp");

const u16 gTilesetAnims_Slateport0_Frame1[] = INCBIN_U16("data/tilesets/secondary/slateport/anim/1.4bpp");

const u16 gTilesetAnims_Slateport0_Frame2[] = INCBIN_U16("data/tilesets/secondary/slateport/anim/2.4bpp");

const u16 gTilesetAnims_Slateport0_Frame3[] = INCBIN_U16("data/tilesets/secondary/slateport/anim/3.4bpp");

const u16 *const gTilesetAnims_Slateport0[] = {
    gTilesetAnims_Slateport0_Frame0,
    gTilesetAnims_Slateport0_Frame1,
    gTilesetAnims_Slateport0_Frame2,
    gTilesetAnims_Slateport0_Frame3
};

const u16 gTilesetAnims_InsideBuilding0_Frame0[] = INCBIN_U16("data/tilesets/primary/building/anim/0.4bpp");

const u16 gTilesetAnims_InsideBuilding0_Frame1[] = INCBIN_U16("data/tilesets/primary/building/anim/1.4bpp");

const u16 *const gTilesetAnims_InsideBuilding0[] = {
    gTilesetAnims_InsideBuilding0_Frame0,
    gTilesetAnims_InsideBuilding0_Frame1
};

const u16 gTilesetAnims_SootopolisGym0_Frame0[] = INCBIN_U16("data/tilesets/secondary/sootopolis_gym/anim/0/0.4bpp");

const u16 gTilesetAnims_SootopolisGym0_Frame1[] = INCBIN_U16("data/tilesets/secondary/sootopolis_gym/anim/0/1.4bpp");

const u16 gTilesetAnims_SootopolisGym0_Frame2[] = INCBIN_U16("data/tilesets/secondary/sootopolis_gym/anim/0/2.4bpp");

const u16 gTilesetAnims_SootopolisGym1_Frame0[] = INCBIN_U16("data/tilesets/secondary/sootopolis_gym/anim/1/0.4bpp");

const u16 gTilesetAnims_SootopolisGym1_Frame1[] = INCBIN_U16("data/tilesets/secondary/sootopolis_gym/anim/1/1.4bpp");

const u16 gTilesetAnims_SootopolisGym1_Frame2[] = INCBIN_U16("data/tilesets/secondary/sootopolis_gym/anim/1/2.4bpp");

const u16 *const gTilesetAnims_SootopolisGym0[] = {
    gTilesetAnims_SootopolisGym0_Frame0,
    gTilesetAnims_SootopolisGym0_Frame1,
    gTilesetAnims_SootopolisGym0_Frame2
};

const u16 *const gTilesetAnims_SootopolisGym1[] = {
    gTilesetAnims_SootopolisGym1_Frame0,
    gTilesetAnims_SootopolisGym1_Frame1,
    gTilesetAnims_SootopolisGym1_Frame2
};

const u16 gTilesetAnims_EliteFour0_Frame0[] = INCBIN_U16("data/tilesets/secondary/elite_four/anim/1/0.4bpp");

const u16 gTilesetAnims_EliteFour0_Frame1[] = INCBIN_U16("data/tilesets/secondary/elite_four/anim/1/1.4bpp");

const u16 gTilesetAnims_EliteFour1_Frame0[] = INCBIN_U16("data/tilesets/secondary/elite_four/anim/0/0.4bpp");

const u16 gTilesetAnims_EliteFour1_Frame1[] = INCBIN_U16("data/tilesets/secondary/elite_four/anim/0/1.4bpp");

const u16 gTilesetAnims_EliteFour1_Frame2[] = INCBIN_U16("data/tilesets/secondary/elite_four/anim/0/2.4bpp");

const u16 gTilesetAnims_EliteFour1_Frame3[] = INCBIN_U16("data/tilesets/secondary/elite_four/anim/0/3.4bpp");

const u16 tileset_anims_space_5[16] = {};

const u16 *const gTilesetAnims_EliteFour1[] = {
    gTilesetAnims_EliteFour1_Frame0,
    gTilesetAnims_EliteFour1_Frame1,
    gTilesetAnims_EliteFour1_Frame2,
    gTilesetAnims_EliteFour1_Frame3
};

const u16 *const gTilesetAnims_EliteFour0[] = {
    gTilesetAnims_EliteFour0_Frame0,
    gTilesetAnims_EliteFour0_Frame1
};

const u16 gTilesetAnims_MauvilleGym0_Frame0[] = INCBIN_U16("data/tilesets/secondary/mauville_gym/anim/0.4bpp");

const u16 gTilesetAnims_MauvilleGym0_Frame1[] = INCBIN_U16("data/tilesets/secondary/mauville_gym/anim/1.4bpp");

const u16 tileset_anims_space_6[16] = {};

const u16 *const gTilesetAnims_MauvilleGym0[] = {
    gTilesetAnims_MauvilleGym0_Frame0,
    gTilesetAnims_MauvilleGym0_Frame1
};

const u16 gTilesetAnims_BikeShop0_Frame0[] = INCBIN_U16("data/tilesets/secondary/bike_shop/anim/0.4bpp");

const u16 gTilesetAnims_BikeShop0_Frame1[] = INCBIN_U16("data/tilesets/secondary/bike_shop/anim/1.4bpp");

const u16 tileset_anims_space_7[16] = {};

const u16 *const gTilesetAnims_BikeShop0[] = {
    gTilesetAnims_BikeShop0_Frame0,
    gTilesetAnims_BikeShop0_Frame1
};

const u16 gTilesetAnims_Sootopolis0_Frame0[] = INCBIN_U16("data/tilesets/secondary/sootopolis/anim/0.4bpp");

const u16 gTilesetAnims_Sootopolis0_Frame1[] = INCBIN_U16("data/tilesets/secondary/sootopolis/anim/1.4bpp");

const u16 gTilesetAnims_Sootopolis0_Frame2[] = INCBIN_U16("data/tilesets/secondary/sootopolis/anim/2.4bpp");

const u16 gTilesetAnims_Sootopolis0_Frame3[] = INCBIN_U16("data/tilesets/secondary/sootopolis/anim/3.4bpp");

const u16 gTilesetAnims_Sootopolis0_Frame4[] = INCBIN_U16("data/tilesets/secondary/sootopolis/anim/4.4bpp");

const u16 gTilesetAnims_Sootopolis0_Frame5[] = INCBIN_U16("data/tilesets/secondary/sootopolis/anim/5.4bpp");

const u16 gTilesetAnims_Sootopolis0_Frame6[] = INCBIN_U16("data/tilesets/secondary/sootopolis/anim/6.4bpp");

const u16 gTilesetAnims_Sootopolis0_Frame7[] = INCBIN_U16("data/tilesets/secondary/sootopolis/anim/7.4bpp");

const u16 tileset_anims_space_8[16] = {};

const u16 gTilesetAnims_Unused1_Frame0[] = INCBIN_U16("data/tilesets/secondary/unused_1/0.4bpp");

const u16 gTilesetAnims_Unused1_Frame1[] = INCBIN_U16("data/tilesets/secondary/unused_1/1.4bpp");

const u16 gTilesetAnims_Unused1_Frame2[] = INCBIN_U16("data/tilesets/secondary/unused_1/2.4bpp");

const u16 gTilesetAnims_Unused1_Frame3[] = INCBIN_U16("data/tilesets/secondary/unused_1/3.4bpp");

const u16 *const gTilesetAnims_Sootopolis0[] = {
    gTilesetAnims_Sootopolis0_Frame0,
    gTilesetAnims_Sootopolis0_Frame1,
    gTilesetAnims_Sootopolis0_Frame2,
    gTilesetAnims_Sootopolis0_Frame3,
    gTilesetAnims_Sootopolis0_Frame4,
    gTilesetAnims_Sootopolis0_Frame5,
    gTilesetAnims_Sootopolis0_Frame6,
    gTilesetAnims_Sootopolis0_Frame7
};

const u16 gTilesetAnims_BattlePyramid0_Frame0[] = INCBIN_U16("data/tilesets/secondary/battle_pyramid/anim/0/0.4bpp");

const u16 gTilesetAnims_BattlePyramid0_Frame1[] = INCBIN_U16("data/tilesets/secondary/battle_pyramid/anim/0/1.4bpp");

const u16 gTilesetAnims_BattlePyramid0_Frame2[] = INCBIN_U16("data/tilesets/secondary/battle_pyramid/anim/0/2.4bpp");

const u16 tileset_anims_space_9[16] = {};

const u16 gTilesetAnims_BattlePyramid1_Frame0[] = INCBIN_U16("data/tilesets/secondary/battle_pyramid/anim/1/0.4bpp");

const u16 gTilesetAnims_BattlePyramid1_Frame1[] = INCBIN_U16("data/tilesets/secondary/battle_pyramid/anim/1/1.4bpp");

const u16 gTilesetAnims_BattlePyramid1_Frame2[] = INCBIN_U16("data/tilesets/secondary/battle_pyramid/anim/1/2.4bpp");

const u16 tileset_anims_space_10[7808] = {};

const u16 gTilesetAnims_Unused2_Frame0[] = INCBIN_U16("data/tilesets/secondary/unused_2/0.4bpp");

const u16 tileset_anims_space_11[224] = {};

const u16 gTilesetAnims_Unused2_Frame1[] = INCBIN_U16("data/tilesets/secondary/unused_2/1.4bpp");

const u16 *const gTilesetAnims_BattlePyramid0[] = {
    gTilesetAnims_BattlePyramid0_Frame0,
    gTilesetAnims_BattlePyramid0_Frame1,
    gTilesetAnims_BattlePyramid0_Frame2
};

const u16 *const gTilesetAnims_BattlePyramid1[] = {
    gTilesetAnims_BattlePyramid1_Frame0,
    gTilesetAnims_BattlePyramid1_Frame1,
    gTilesetAnims_BattlePyramid1_Frame2
};

extern const u16 gTilesetAnims_BattleDomePals0_0[];
extern const u16 gTilesetAnims_BattleDomePals0_1[];
extern const u16 gTilesetAnims_BattleDomePals0_2[];
extern const u16 gTilesetAnims_BattleDomePals0_3[];

static const u16 *const gTilesetAnims_BattleDomePals0[] = {
    gTilesetAnims_BattleDomePals0_0,
    gTilesetAnims_BattleDomePals0_1,
    gTilesetAnims_BattleDomePals0_2,
    gTilesetAnims_BattleDomePals0_3,
};

// .text

static void ResetTilesetAnimBuffer(void)
{
    sTilesetDMA3TransferBufferSize = 0;
    CpuFill32(0, sTilesetDMA3TransferBuffer, sizeof sTilesetDMA3TransferBuffer);
}

static void AppendTilesetAnimToBuffer(const u16 *src, u16 *dest, u16 size)
{
    if (sTilesetDMA3TransferBufferSize < 20)
    {
        sTilesetDMA3TransferBuffer[sTilesetDMA3TransferBufferSize].src = src;
        sTilesetDMA3TransferBuffer[sTilesetDMA3TransferBufferSize].dest = dest;
        sTilesetDMA3TransferBuffer[sTilesetDMA3TransferBufferSize].size = size;
        sTilesetDMA3TransferBufferSize ++;
    }
}

void TransferTilesetAnimsBuffer(void)
{
    int i;

    for (i = 0; i < sTilesetDMA3TransferBufferSize; i ++)
    {
        DmaCopy16(3, sTilesetDMA3TransferBuffer[i].src, sTilesetDMA3TransferBuffer[i].dest, sTilesetDMA3TransferBuffer[i].size);
    }
    sTilesetDMA3TransferBufferSize = 0;
}

void cur_mapheader_run_tileset_funcs_after_some_cpuset(void)
{
    ResetTilesetAnimBuffer();
    cur_mapheader_run_tileset1_func();
    cur_mapheader_run_tileset2_func();
}

void sub_80A0A2C(void)
{
    cur_mapheader_run_tileset2_func();
}

void sub_80A0A38(void)
{
    ResetTilesetAnimBuffer();
    if (++sPrimaryTilesetCBCounter >= sPrimaryTilesetCBBufferSize)
        sPrimaryTilesetCBCounter = 0;
    if (++sSecondaryTilesetCBCounter >= sSecondaryTilesetCBBufferSize)
        sSecondaryTilesetCBCounter = 0;
    if (sPrimaryTilesetCB)
        sPrimaryTilesetCB(sPrimaryTilesetCBCounter);
    if (sSecondaryTilesetCB)
        sSecondaryTilesetCB(sSecondaryTilesetCBCounter);
}

static void cur_mapheader_run_tileset1_func(void)
{
    sPrimaryTilesetCBCounter = 0;
    sPrimaryTilesetCBBufferSize = 0;
    sPrimaryTilesetCB = NULL;
    if (gMapHeader.mapLayout->primaryTileset && gMapHeader.mapLayout->primaryTileset->callback)
        gMapHeader.mapLayout->primaryTileset->callback();
}

static void cur_mapheader_run_tileset2_func(void)
{
    sSecondaryTilesetCBCounter = 0;
    sSecondaryTilesetCBBufferSize = 0;
    sSecondaryTilesetCB = NULL;
    if (gMapHeader.mapLayout->secondaryTileset && gMapHeader.mapLayout->secondaryTileset->callback)
        gMapHeader.mapLayout->secondaryTileset->callback();
}

void TilesetCb_General(void)
{
    static void sub_80A0B70(u16);

    sPrimaryTilesetCBCounter = 0;
    sPrimaryTilesetCBBufferSize = 0x100;
    sPrimaryTilesetCB = sub_80A0B70;
}

void TilesetCb_InsideBuilding(void)
{
    static void sub_80A0BB4(u16);

    sPrimaryTilesetCBCounter = 0;
    sPrimaryTilesetCBBufferSize = 0x100;
    sPrimaryTilesetCB = sub_80A0BB4;
}

static void sub_80A0B70(u16 timer)
{
    static void gTilesetAnims_Flower(u16);
    static void gTilesetAnims_Water(u16);
    static void gTilesetAnims_SandWaterEdge(u16);
    static void gTilesetAnims_Waterfall(u16);
    static void gTilesetAnims_LandWaterEdge (u16);

    if ((timer & 0x0F) == 0)
        gTilesetAnims_Flower(timer >> 4);
    if ((timer & 0x0F) == 1)
        gTilesetAnims_Water(timer >> 4);
    if ((timer & 0x0F) == 2)
        gTilesetAnims_SandWaterEdge(timer >> 4);
    if ((timer & 0x0F) == 3)
        gTilesetAnims_Waterfall(timer >> 4);
    if ((timer & 0x0F) == 4)
        gTilesetAnims_LandWaterEdge (timer >> 4);
}

static void sub_80A0BB4(u16 timer)
{
    static void sub_80A1688(u16);

    if ((timer & 0x7) == 0)
        sub_80A1688(timer >> 3);
}

static void gTilesetAnims_Flower(u16 timer)
{
    u16 idx;

    idx = timer % 4;
    AppendTilesetAnimToBuffer(gTilesetAnims_General0[idx], (u16 *)(BG_VRAM + TILE_OFFSET_4BPP(508)), 0x80);
}

static void gTilesetAnims_Water(u16 timer)
{
    u8 idx;

    idx = timer % 8;
    AppendTilesetAnimToBuffer(gTilesetAnims_General1[idx], (u16 *)(BG_VRAM + TILE_OFFSET_4BPP(432)), 0x3C0);
}

static void gTilesetAnims_SandWaterEdge(u16 timer)
{
    u16 idx;

    idx = timer % 8;
    AppendTilesetAnimToBuffer(gTilesetAnims_General2[idx], (u16 *)(BG_VRAM + TILE_OFFSET_4BPP(464)), 0x140);
}

static void gTilesetAnims_Waterfall(u16 timer)
{
    u16 idx;

    idx = timer % 4;
    AppendTilesetAnimToBuffer(gTilesetAnims_General3[idx], (u16 *)(BG_VRAM + TILE_OFFSET_4BPP(496)), 0xc0);
}

void TilesetCb_Petalburg(void)
{
    sSecondaryTilesetCBCounter = 0;
    sSecondaryTilesetCBBufferSize = sPrimaryTilesetCBBufferSize;
    sSecondaryTilesetCB = NULL;
}

void TilesetCb_Rustboro(void)
{
    static void sub_80A103C(u16);

    sSecondaryTilesetCBCounter = 0;
    sSecondaryTilesetCBBufferSize = sPrimaryTilesetCBBufferSize;
    sSecondaryTilesetCB = sub_80A103C;
}

void TilesetCb_Dewford(void)
{
    static void sub_80A10B8(u16);

    sSecondaryTilesetCBCounter = 0;
    sSecondaryTilesetCBBufferSize = sPrimaryTilesetCBBufferSize;
    sSecondaryTilesetCB = sub_80A10B8;
}

void TilesetCb_Slateport(void)
{
    static void sub_80A10D0(u16);

    sSecondaryTilesetCBCounter = 0;
    sSecondaryTilesetCBBufferSize = sPrimaryTilesetCBBufferSize;
    sSecondaryTilesetCB = sub_80A10D0;
}

void TilesetCb_Mauville(void)
{
    static void sub_80A10E8(u16);

    sSecondaryTilesetCBCounter = sPrimaryTilesetCBCounter;
    sSecondaryTilesetCBBufferSize = sPrimaryTilesetCBBufferSize;
    sSecondaryTilesetCB = sub_80A10E8;
}

void TilesetCb_Lavaridge(void)
{
    static void sub_80A115C(u16);

    sSecondaryTilesetCBCounter = 0;
    sSecondaryTilesetCBBufferSize = sPrimaryTilesetCBBufferSize;
    sSecondaryTilesetCB = sub_80A115C;
}

void TilesetCb_Fallarbor(void)
{
    sSecondaryTilesetCBCounter = 0;
    sSecondaryTilesetCBBufferSize = sPrimaryTilesetCBBufferSize;
    sSecondaryTilesetCB = NULL;
}

void TilesetCb_Fortree(void)
{
    sSecondaryTilesetCBCounter = 0;
    sSecondaryTilesetCBBufferSize = sPrimaryTilesetCBBufferSize;
    sSecondaryTilesetCB = NULL;
}

void TilesetCb_Lilycove(void)
{
    sSecondaryTilesetCBCounter = 0;
    sSecondaryTilesetCBBufferSize = sPrimaryTilesetCBBufferSize;
    sSecondaryTilesetCB = NULL;
}

void TilesetCb_Mossdeep(void)
{
    sSecondaryTilesetCBCounter = 0;
    sSecondaryTilesetCBBufferSize = sPrimaryTilesetCBBufferSize;
    sSecondaryTilesetCB = NULL;
}

void TilesetCb_EverGrande(void)
{
    static void sub_80A1188(u16);

    sSecondaryTilesetCBCounter = 0;
    sSecondaryTilesetCBBufferSize = sPrimaryTilesetCBBufferSize;
    sSecondaryTilesetCB = sub_80A1188;
}

void TilesetCb_Pacifidlog(void)
{
    static void sub_80A11FC(u16);

    sSecondaryTilesetCBCounter = sPrimaryTilesetCBCounter;
    sSecondaryTilesetCBBufferSize = sPrimaryTilesetCBBufferSize;
    sSecondaryTilesetCB = sub_80A11FC;
}

void TilesetCb_Sootopolis(void)
{
    static void sub_80A122C(u16);

    sSecondaryTilesetCBCounter = 0;
    sSecondaryTilesetCBBufferSize = sPrimaryTilesetCBBufferSize;
    sSecondaryTilesetCB = sub_80A122C;
}

void TilesetCb_BattleFrontierOutsideWest(void)
{
    static void sub_80A127C(u16);

    sSecondaryTilesetCBCounter = 0;
    sSecondaryTilesetCBBufferSize = sPrimaryTilesetCBBufferSize;
    sSecondaryTilesetCB = sub_80A127C;
}

void TilesetCb_BattleFrontierOutsideEast(void)
{
    static void sub_80A1294(u16);

    sSecondaryTilesetCBCounter = 0;
    sSecondaryTilesetCBBufferSize = sPrimaryTilesetCBBufferSize;
    sSecondaryTilesetCB = sub_80A1294;
}

void TilesetCb_Underwater(void)
{
    static void sub_80A1244(u16);

    sSecondaryTilesetCBCounter = 0;
    sSecondaryTilesetCBBufferSize = 128;
    sSecondaryTilesetCB = sub_80A1244;
}

void TilesetCb_SootopolisGym(void)
{
    static void sub_80A15D8(u16);

    sSecondaryTilesetCBCounter = 0;
    sSecondaryTilesetCBBufferSize = 240;
    sSecondaryTilesetCB = sub_80A15D8;
}

void TilesetCb_Cave(void)
{
    static void sub_80A1260(u16);

    sSecondaryTilesetCBCounter = 0;
    sSecondaryTilesetCBBufferSize = sPrimaryTilesetCBBufferSize;
    sSecondaryTilesetCB = sub_80A1260;
}

void TilesetCb_EliteFour(void)
{
    static void sub_80A15F0(u16);

    sSecondaryTilesetCBCounter = 0;
    sSecondaryTilesetCBBufferSize = 128;
    sSecondaryTilesetCB = sub_80A15F0;
}

void TilesetCb_MauvilleGym(void)
{
    static void sub_80A15C0(u16);

    sSecondaryTilesetCBCounter = 0;
    sSecondaryTilesetCBBufferSize = sPrimaryTilesetCBBufferSize;
    sSecondaryTilesetCB = sub_80A15C0;
}

void TilesetCb_BikeShop(void)
{
    static void sub_80A161C(u16);

    sSecondaryTilesetCBCounter = 0;
    sSecondaryTilesetCBBufferSize = sPrimaryTilesetCBBufferSize;
    sSecondaryTilesetCB = sub_80A161C;
}

void TilesetCb_BattlePyramid(void)
{
    static void sub_80A1634(u16);

    sSecondaryTilesetCBCounter = 0;
    sSecondaryTilesetCBBufferSize = sPrimaryTilesetCBBufferSize;
    sSecondaryTilesetCB = sub_80A1634;
}

void TilesetCb_BattleDome(void)
{
    static void sub_80A1658(u16);

    sSecondaryTilesetCBCounter = 0;
    sSecondaryTilesetCBBufferSize = sPrimaryTilesetCBBufferSize;
    sSecondaryTilesetCB = sub_80A1658;
}

static void sub_80A103C(u16 timer)
{
    static void sub_80A1434(u16, u8);
    static void sub_80A1470(u16);

    if ((timer & 0x07) == 0)
    {
        sub_80A1434(timer >> 3, 0);
        sub_80A1470(timer >> 3);
    }
    if ((timer & 0x07) == 1)
        sub_80A1434(timer >> 3, 1);
    if ((timer & 0x07) == 2)
        sub_80A1434(timer >> 3, 2);
    if ((timer & 0x07) == 3)
        sub_80A1434(timer >> 3, 3);
    if ((timer & 0x07) == 4)
        sub_80A1434(timer >> 3, 4);
    if ((timer & 0x07) == 5)
        sub_80A1434(timer >> 3, 5);
    if ((timer & 0x07) == 6)
        sub_80A1434(timer >> 3, 6);
    if ((timer & 0x07) == 7)
        sub_80A1434(timer >> 3, 7);
}

static void sub_80A10B8(u16 timer)
{
    static void sub_80A1520(u16);

    if ((timer & 7) == 0)
        sub_80A1520(timer >> 3);
}

static void sub_80A10D0(u16 timer)
{
    static void sub_80A1598(u16);

    if ((timer & 15) == 0)
        sub_80A1598(timer >> 4);
}

static void sub_80A10E8(u16 timer)
{
    static void sub_80A1394(u16, u8);

    if ((timer & 0x07) == 0)
        sub_80A1394(timer >> 3, 0);
    if ((timer & 0x07) == 1)
        sub_80A1394(timer >> 3, 1);
    if ((timer & 0x07) == 2)
        sub_80A1394(timer >> 3, 2);
    if ((timer & 0x07) == 3)
        sub_80A1394(timer >> 3, 3);
    if ((timer & 0x07) == 4)
        sub_80A1394(timer >> 3, 4);
    if ((timer & 0x07) == 5)
        sub_80A1394(timer >> 3, 5);
    if ((timer & 0x07) == 6)
        sub_80A1394(timer >> 3, 6);
    if ((timer & 0x07) == 7)
        sub_80A1394(timer >> 3, 7);
}

static void sub_80A115C(u16 timer)
{
    static void sub_80A12D4(u8);
    static void sub_80A1498(u16);

    if ((timer & 0x0F) == 0)
        sub_80A12D4(timer >> 4);
    if ((timer & 0x0F) == 1)
        sub_80A1498(timer >> 4);
}

static void sub_80A1188(u16 timer)
{
    static void sub_80A14C0(u16, u8);

    if ((timer & 0x07) == 0)
        sub_80A14C0(timer >> 3, 0);
    if ((timer & 0x07) == 1)
        sub_80A14C0(timer >> 3, 1);
    if ((timer & 0x07) == 2)
        sub_80A14C0(timer >> 3, 2);
    if ((timer & 0x07) == 3)
        sub_80A14C0(timer >> 3, 3);
    if ((timer & 0x07) == 4)
        sub_80A14C0(timer >> 3, 4);
    if ((timer & 0x07) == 5)
        sub_80A14C0(timer >> 3, 5);
    if ((timer & 0x07) == 6)
        sub_80A14C0(timer >> 3, 6);
    if ((timer & 0x07) == 7)
        sub_80A14C0(timer >> 3, 7);
}

static void sub_80A11FC(u16 timer)
{
    static void sub_80A131C(u8);
    static void sub_80A136C(u8);

    if ((timer & 0x0F) == 0)
        sub_80A131C(timer >> 4);
    if ((timer & 0x0F) == 1)
        sub_80A136C(timer >> 4);
}

static void sub_80A122C(u16 timer)
{
    static void sub_80A1798(u16);

    if ((timer & 0x0F) == 0)
        sub_80A1798(timer >> 4);
}

static void sub_80A1244(u16 timer)
{
    static void sub_80A1344(u8);

    if ((timer & 0x0F) == 0)
        sub_80A1344(timer >> 4);
}

static void sub_80A1260(u16 timer)
{
    static void sub_80A14F8(u16);

    if ((timer & 0x0F) == 1)
        sub_80A14F8(timer >> 4);
}

static void sub_80A127C(u16 timer)
{
    static void sub_80A1548(u16);

    if ((timer & 0x07) == 0)
        sub_80A1548(timer >> 3);
}

static void sub_80A1294(u16 timer)
{
    static void sub_80A1570(u16);

    if ((timer & 0x07) == 0)
        sub_80A1570(timer >> 3);
}

static void gTilesetAnims_LandWaterEdge (u16 timer)
{
    u16 idx;

    idx = timer % 4;
    AppendTilesetAnimToBuffer(gTilesetAnims_General4[idx], (u16 *)(BG_VRAM + TILE_OFFSET_4BPP(480)), 0x140);
}

static void sub_80A12D4(u8 timer)
{
    u8 idx;

    idx = timer % 4;
    AppendTilesetAnimToBuffer(gTilesetAnims_Lavaridge0[idx], (u16 *)(BG_VRAM + TILE_OFFSET_4BPP(NUM_TILES_IN_PRIMARY + 288)), 0x80);

    idx = (timer + 2) % 4;
    AppendTilesetAnimToBuffer(gTilesetAnims_Lavaridge0[idx], (u16 *)(BG_VRAM + TILE_OFFSET_4BPP(NUM_TILES_IN_PRIMARY + 292)), 0x80);
}

static void sub_80A131C(u8 timer)
{
    u8 idx;

    idx = timer % 4;
    AppendTilesetAnimToBuffer(gTilesetAnims_Pacifidlog0[idx], (u16 *)(BG_VRAM + TILE_OFFSET_4BPP(NUM_TILES_IN_PRIMARY + 464)), 0x3C0);
}

static void sub_80A1344(u8 timer)
{
    u8 idx;

    idx = timer % 4;
    AppendTilesetAnimToBuffer(gTilesetAnims_Underwater0[idx], (u16 *)(BG_VRAM + TILE_OFFSET_4BPP(NUM_TILES_IN_PRIMARY + 496)), 0x80);
}

static void sub_80A136C(u8 timer)
{
    u8 idx;

    idx = timer % 8;
    AppendTilesetAnimToBuffer(gTilesetAnims_Pacifidlog1[idx], (u16 *)(BG_VRAM + TILE_OFFSET_4BPP(NUM_TILES_IN_PRIMARY + 496)), 0x100);
}

static void sub_80A1394(u16 timer_div, u8 timer_mod)
{
    timer_div -= timer_mod;
    if (timer_div < 12) // almost certainly a typo
    {
        timer_div %= 12;
        AppendTilesetAnimToBuffer(gTilesetAnims_Mauville0a[timer_div], gTilesetAnims_MauvilleVDests0[timer_mod], 0x80);
        AppendTilesetAnimToBuffer(gTilesetAnims_Mauville0b[timer_div], gTilesetAnims_MauvilleVDests1[timer_mod], 0x80);
    }
    else
    {
        timer_div %= 4;
        AppendTilesetAnimToBuffer(gTilesetAnims_Mauville1a[timer_div], gTilesetAnims_MauvilleVDests0[timer_mod], 0x80);
        AppendTilesetAnimToBuffer(gTilesetAnims_Mauville1b[timer_div], gTilesetAnims_MauvilleVDests1[timer_mod], 0x80);
    }
}

static void sub_80A1434(u16 timer_div, u8 timer_mod)
{
    timer_div -= timer_mod;
    timer_div %= 8;
    if (gTilesetAnims_Rustboro0[timer_div])
        AppendTilesetAnimToBuffer(gTilesetAnims_Rustboro0[timer_div], gTilesetAnims_RustboroVDests0[timer_mod], 0x80);
}

static void sub_80A1470(u16 timer)
{
    u16 idx;

    idx = timer % 2;
    AppendTilesetAnimToBuffer(gTilesetAnims_Rustboro1[idx], (u16 *)(BG_VRAM + TILE_OFFSET_4BPP(NUM_TILES_IN_PRIMARY + 448)), 0x80);
}

static void sub_80A1498(u16 timer)
{
    u16 idx;

    idx = timer % 4;
    AppendTilesetAnimToBuffer(gTilesetAnims_Lavaridge1_Cave0[idx], (u16 *)(BG_VRAM + TILE_OFFSET_4BPP(NUM_TILES_IN_PRIMARY + 160)), 0x80);
}

static void sub_80A14C0(u16 timer_div, u8 timer_mod)
{
    timer_div -= timer_mod;
    timer_div %= 8;

    AppendTilesetAnimToBuffer(gTilesetAnims_EverGrande0[timer_div], gTilesetAnims_EverGrandeVDests0[timer_mod], 0x80);
}

static void sub_80A14F8(u16 timer)
{
    u16 idx;

    idx = timer % 4;
    AppendTilesetAnimToBuffer(gTilesetAnims_Lavaridge1_Cave0[idx], (u16 *)(BG_VRAM + TILE_OFFSET_4BPP(NUM_TILES_IN_PRIMARY + 416)), 0x80);
}

static void sub_80A1520(u16 timer)
{
    u16 idx;

    idx = timer % 4;
    AppendTilesetAnimToBuffer(gTilesetAnims_Dewford0[idx], (u16 *)(BG_VRAM + TILE_OFFSET_4BPP(NUM_TILES_IN_PRIMARY + 170)), 0xC0);
}

static void sub_80A1548(u16 timer)
{
    u16 idx;

    idx = timer % 4;
    AppendTilesetAnimToBuffer(gTilesetAnims_BattleFrontierOutsideWest0[idx], (u16 *)(BG_VRAM + TILE_OFFSET_4BPP(NUM_TILES_IN_PRIMARY + 218)), 0xC0);
}

static void sub_80A1570(u16 timer)
{
    u16 idx;

    idx = timer % 4;
    AppendTilesetAnimToBuffer(gTilesetAnims_BattleFrontierOutsideEast0[idx], (u16 *)(BG_VRAM + TILE_OFFSET_4BPP(NUM_TILES_IN_PRIMARY + 218)), 0xC0);
}

static void sub_80A1598(u16 timer)
{
    u16 idx;

    idx = timer % 4;
    AppendTilesetAnimToBuffer(gTilesetAnims_Slateport0[idx], (u16 *)(BG_VRAM + TILE_OFFSET_4BPP(NUM_TILES_IN_PRIMARY + 224)), 0x80);
}

static void sub_80A15C0(u16 timer)
{
    static void sub_80A1748(u16);

    if ((timer & 1) == 0)
        sub_80A1748(timer >> 1);
}

static void sub_80A15D8(u16 timer)
{
    static void sub_80A16B0(u16);

    if ((timer & 7) == 0)
        sub_80A16B0(timer >> 3);
}

static void sub_80A15F0(u16 timer)
{
    static void sub_80A1720(u16);
    static void sub_80A16F8(u16);

    if ((timer & 0x3f) == 1)
        sub_80A1720(timer >> 6);
    if ((timer & 0x07) == 1)
        sub_80A16F8(timer >> 3);
}
static void sub_80A161C(u16 timer)
{
    static void sub_80A1770(u16);

    if ((timer & 3) == 0)
        sub_80A1770(timer >> 2);
}

static void sub_80A1634(u16 timer)
{
    static void sub_80A17C0(u16);
    static void sub_80A17EC(u16);

    if ((timer & 7) == 0)
    {
        sub_80A17C0(timer >> 3);
        sub_80A17EC(timer >> 3);
    }
}

static void sub_80A1658(u16 timer)
{
    static void sub_80A1818(u16);

    if ((timer & 3) == 0)
        sub_80A1818(timer >> 2);
}

static void sub_80A1670(u16 timer)
{
    static void sub_80A1884(u16);

    if ((timer & 3) == 0)
        sub_80A1884(timer >> 2);
}

static void sub_80A1688(u16 timer)
{
    u16 idx;

    idx = timer % 2;
    AppendTilesetAnimToBuffer(gTilesetAnims_InsideBuilding0[idx], (u16 *)(BG_VRAM + TILE_OFFSET_4BPP(496)), 0x80);
}

static void sub_80A16B0(u16 timer)
{
    u16 idx;

    idx = timer % 3;
    AppendTilesetAnimToBuffer(gTilesetAnims_SootopolisGym0[idx], (u16 *)(BG_VRAM + TILE_OFFSET_4BPP(NUM_TILES_IN_PRIMARY + 496)), 0x180);
    AppendTilesetAnimToBuffer(gTilesetAnims_SootopolisGym1[idx], (u16 *)(BG_VRAM + TILE_OFFSET_4BPP(NUM_TILES_IN_PRIMARY + 464)), 0x280);
}

static void sub_80A16F8(u16 timer)
{
    u16 idx;

    idx = timer % 4;
    AppendTilesetAnimToBuffer(gTilesetAnims_EliteFour1[idx], (u16 *)(BG_VRAM + TILE_OFFSET_4BPP(NUM_TILES_IN_PRIMARY + 504)), 0x20);
}

static void sub_80A1720(u16 timer)
{
    u16 idx;

    idx = timer % 2;
    AppendTilesetAnimToBuffer(gTilesetAnims_EliteFour0[idx], (u16 *)(BG_VRAM + TILE_OFFSET_4BPP(NUM_TILES_IN_PRIMARY + 480)), 0x80);
}

static void sub_80A1748(u16 timer)
{
    u16 idx;

    idx = timer % 2;
    AppendTilesetAnimToBuffer(gTilesetAnims_MauvilleGym0[idx], (u16 *)(BG_VRAM + TILE_OFFSET_4BPP(NUM_TILES_IN_PRIMARY + 144)), 0x200);
}

static void sub_80A1770(u16 timer)
{
    u16 idx;

    idx = timer % 2;
    AppendTilesetAnimToBuffer(gTilesetAnims_BikeShop0[idx], (u16 *)(BG_VRAM + TILE_OFFSET_4BPP(NUM_TILES_IN_PRIMARY + 496)), 0x120);
}

static void sub_80A1798(u16 timer)
{
    u16 idx;

    idx = timer % 8;
    AppendTilesetAnimToBuffer(gTilesetAnims_Sootopolis0[idx], (u16 *)(BG_VRAM + TILE_OFFSET_4BPP(NUM_TILES_IN_PRIMARY + 240)), 0xc00);
}

static void sub_80A17C0(u16 timer)
{
    u16 idx;

    idx = timer % 3;
    AppendTilesetAnimToBuffer(gTilesetAnims_BattlePyramid0[idx], (u16 *)(BG_VRAM + TILE_OFFSET_4BPP(NUM_TILES_IN_PRIMARY + 151)), 0x100);
}

static void sub_80A17EC(u16 timer)
{
    u16 idx;

    idx = timer % 3;
    AppendTilesetAnimToBuffer(gTilesetAnims_BattlePyramid1[idx], (u16 *)(BG_VRAM + TILE_OFFSET_4BPP(NUM_TILES_IN_PRIMARY + 135)), 0x100);
}

static void sub_80A1818(u16 a1)
{
    CpuCopy16(gTilesetAnims_BattleDomePals0[a1 & 0x3], gPlttBufferUnfaded + 0x80, 32);
    BlendPalette(0x80, 0x10, gPaletteFade.y, gPaletteFade.blendColor & 0x7FFF);
    if ((u8)FindTaskIdByFunc(TransitionPhase1_Task_RunFuncs) != 0xFF )
    {
        sSecondaryTilesetCB = sub_80A1670;
        sSecondaryTilesetCBBufferSize = 0x20;
    }
}

static void sub_80A1884(u16 a1)
{
    CpuCopy16(gTilesetAnims_BattleDomePals0[a1 & 0x3], gPlttBufferUnfaded + 0x80, 32);
    if ((u8)FindTaskIdByFunc(TransitionPhase1_Task_RunFuncs) == 0xFF )
    {
        BlendPalette(0x80, 0x10, gPaletteFade.y, gPaletteFade.blendColor & 0x7FFF);
        if (!--sSecondaryTilesetCBBufferSize)
            sSecondaryTilesetCB = NULL;
    }
}
