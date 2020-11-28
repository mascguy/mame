// license:BSD-3-Clause
// copyright-holders:Nicola Salmoria
/***************************************************************************

  Galaxian hardware family (old)

  This include file is used by the following drivers:
    - dambustr.cpp
    - galaxold.cpp
    - scramble.cpp
    - scobra.cpp

***************************************************************************/
#ifndef MAME_INCLUDES_GALAXOLD_H
#define MAME_INCLUDES_GALAXOLD_H

#pragma once

#include "machine/7474.h"
#include "machine/timer.h"
#include "emupal.h"
#include "screen.h"
#include "tilemap.h"

/* star circuit */
#define STAR_COUNT  252
struct star_gold
{
	int x, y, color;
};

class galaxold_state : public driver_device
{
public:
	galaxold_state(const machine_config &mconfig, device_type type, const char *tag)
		: driver_device(mconfig, type, tag)
		, m_maincpu(*this, "maincpu")
		, m_audiocpu(*this, "audiocpu")
		, m_7474_9m_1(*this, "7474_9m_1")
		, m_7474_9m_2(*this, "7474_9m_2")
		, m_gfxdecode(*this, "gfxdecode")
		, m_screen(*this, "screen")
		, m_palette(*this, "palette")
		, m_videoram(*this,"videoram")
		, m_spriteram(*this,"spriteram")
		, m_spriteram2(*this,"spriteram2")
		, m_attributesram(*this,"attributesram")
		, m_bulletsram(*this,"bulletsram")
		, m_rockclim_videoram(*this,"rockclim_vram")
		, m_racknrol_tiles_bank(*this,"racknrol_tbank")
		, m_leds(*this, "led%u", 0U)
		, m_leftclip(2)
	{ }

	/* devices */
	required_device<cpu_device> m_maincpu;
	optional_device<cpu_device> m_audiocpu;
	optional_device<ttl7474_device> m_7474_9m_1;
	optional_device<ttl7474_device> m_7474_9m_2;
	required_device<gfxdecode_device> m_gfxdecode;
	required_device<screen_device> m_screen;
	required_device<palette_device> m_palette;

	/* memory pointers */
	required_shared_ptr<uint8_t> m_videoram;
	required_shared_ptr<uint8_t> m_spriteram;
	optional_shared_ptr<uint8_t> m_spriteram2;
	required_shared_ptr<uint8_t> m_attributesram;
	optional_shared_ptr<uint8_t> m_bulletsram;
	optional_shared_ptr<uint8_t> m_rockclim_videoram;
	optional_shared_ptr<uint8_t> m_racknrol_tiles_bank;
	output_finder<2> m_leds;

	int m_irq_line;
	uint8_t m__4in1_bank;
	tilemap_t *m_bg_tilemap;
	tilemap_t *m_rockclim_tilemap;
	int m_spriteram2_present;
	uint8_t m_gfxbank[5];
	uint8_t m_flipscreen_x;
	uint8_t m_flipscreen_y;
	uint8_t m_color_mask;
	tilemap_t *m_dambustr_tilemap2;
	std::unique_ptr<uint8_t[]> m_dambustr_videoram2;
	int m_leftclip;

	void (galaxold_state::*m_modify_charcode)(uint16_t *code, uint8_t x);     /* function to call to do character banking */
	void (galaxold_state::*m_modify_spritecode)(uint8_t *spriteram, int*, int*, int*, int); /* function to call to do sprite banking */
	void (galaxold_state::*m_modify_color)(uint8_t *color);   /* function to call to do modify how the color codes map to the PROM */
	void (galaxold_state::*m_modify_ypos)(uint8_t*);  /* function to call to do modify how vertical positioning bits are connected */

	uint8_t m_timer_adjusted;
	uint8_t m_darkplnt_bullet_color;
	void (galaxold_state::*m_draw_bullets)(bitmap_ind16 &,const rectangle &, int, int, int);  /* function to call to draw a bullet */

	uint8_t m_background_enable;
	uint8_t m_background_red;
	uint8_t m_background_green;
	uint8_t m_background_blue;
	void (galaxold_state::*m_draw_background)(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);   /* function to call to draw the background */
	uint16_t m_rockclim_v;
	uint16_t m_rockclim_h;
	int m_dambustr_bg_split_line;
	int m_dambustr_bg_color_1;
	int m_dambustr_bg_color_2;
	int m_dambustr_bg_priority;
	int m_dambustr_char_bank;
	std::unique_ptr<bitmap_ind16> m_dambustr_tmpbitmap;

	void (galaxold_state::*m_draw_stars)(bitmap_ind16 &, const rectangle &);      /* function to call to draw the star layer */
	int m_stars_colors_start;
	int32_t m_stars_scrollpos;
	uint8_t m_stars_on;
	uint8_t m_stars_blink_state;
	emu_timer *m_stars_blink_timer;
	emu_timer *m_stars_scroll_timer;
	struct star_gold m_stars[STAR_COUNT];

	uint8_t drivfrcg_port0_r();
	uint8_t scrambler_protection_2_r();
	uint8_t scramb2_protection_r();
	uint8_t scramb2_port0_r(offs_t offset);
	uint8_t scramb2_port1_r(offs_t offset);
	uint8_t scramb2_port2_r(offs_t offset);
	uint8_t hexpoola_data_port_r();
	uint8_t bullsdrtg_data_port_r();
	void galaxold_nmi_enable_w(uint8_t data);
	void galaxold_coin_lockout_w(uint8_t data);
	void galaxold_coin_counter_w(offs_t offset, uint8_t data);
	void galaxold_coin_counter_1_w(uint8_t data);
	void galaxold_coin_counter_2_w(uint8_t data);
	void galaxold_leds_w(offs_t offset, uint8_t data);
	uint8_t scramblb_protection_1_r();
	uint8_t scramblb_protection_2_r();
	void _4in1_bank_w(uint8_t data);
	void racknrol_tiles_bank_w(offs_t offset, uint8_t data);
	void galaxold_videoram_w(offs_t offset, uint8_t data);
	uint8_t galaxold_videoram_r(offs_t offset);
	void galaxold_attributesram_w(offs_t offset, uint8_t data);
	void galaxold_flip_screen_x_w(uint8_t data);
	void galaxold_flip_screen_y_w(uint8_t data);
	void hotshock_flip_screen_w(uint8_t data);
	void scrambold_background_enable_w(uint8_t data);
	void scrambold_background_red_w(uint8_t data);
	void scrambold_background_green_w(uint8_t data);
	void scrambold_background_blue_w(uint8_t data);
	void galaxold_stars_enable_w(uint8_t data);
	void darkplnt_bullet_color_w(uint8_t data);
	void galaxold_gfxbank_w(offs_t offset, uint8_t data);
	void rockclim_videoram_w(offs_t offset, uint8_t data);
	void rockclim_scroll_w(offs_t offset, uint8_t data);
	void guttang_rombank_w(uint8_t data);
	uint8_t rockclim_videoram_r(offs_t offset);
	void dambustr_bg_split_line_w(uint8_t data);
	void dambustr_bg_color_w(uint8_t data);
	DECLARE_WRITE_LINE_MEMBER(galaxold_7474_9m_2_q_callback);
	DECLARE_WRITE_LINE_MEMBER(galaxold_7474_9m_1_callback);
	uint8_t rescueb_a002_r() { return 0xfc; }
	template <int Mask> DECLARE_READ_LINE_MEMBER(_4in1_fake_port_r);
	template <int Mask> DECLARE_READ_LINE_MEMBER(vpool_lives_r);
	template <int Mask> DECLARE_CUSTOM_INPUT_MEMBER(ckongg_coinage_r);
	template <int Mask> DECLARE_CUSTOM_INPUT_MEMBER(dkongjrm_coinage_r);

	void init_bullsdrtg();
	void init_ladybugg();
	void init_4in1();
	void init_guttangt();
	void init_ckonggx();

	TILE_GET_INFO_MEMBER(drivfrcg_get_tile_info);
	TILE_GET_INFO_MEMBER(racknrol_get_tile_info);
	TILE_GET_INFO_MEMBER(dambustr_get_tile_info2);
	TILE_GET_INFO_MEMBER(get_tile_info);
	TILE_GET_INFO_MEMBER(rockclim_get_tile_info);
	TILE_GET_INFO_MEMBER(harem_get_tile_info);

	DECLARE_MACHINE_RESET(galaxold);
	DECLARE_MACHINE_RESET(devilfsg);
	DECLARE_MACHINE_RESET(hunchbkg);

	void galaxold_palette(palette_device &palette);
	void rockclim_palette(palette_device &palette) const;
	void scrambold_palette(palette_device &palette);
	void stratgyx_palette(palette_device &palette);
	void darkplnt_palette(palette_device &palette) const;
	void minefld_palette(palette_device &palette);
	void rescue_palette(palette_device &palette);
	void mariner_palette(palette_device &palette);
	void dambustr_palette(palette_device &palette);
	void turtles_palette(palette_device &palette);

	DECLARE_VIDEO_START(galaxold);
	DECLARE_VIDEO_START(drivfrcg);
	DECLARE_VIDEO_START(racknrol);
	DECLARE_VIDEO_START(mooncrst);
	DECLARE_VIDEO_START(scrambold);
	DECLARE_VIDEO_START(newsin7);
	DECLARE_VIDEO_START(pisces);
	DECLARE_VIDEO_START(dkongjrm);
	DECLARE_VIDEO_START(dkongjrmc);
	DECLARE_VIDEO_START(rockclim);
	DECLARE_VIDEO_START(galaxold_plain);
	DECLARE_VIDEO_START(ozon1);
	DECLARE_VIDEO_START(bongo);
	DECLARE_VIDEO_START(ckongs);
	DECLARE_VIDEO_START(darkplnt);
	DECLARE_VIDEO_START(rescue);
	DECLARE_VIDEO_START(minefld);
	DECLARE_VIDEO_START(stratgyx);
	DECLARE_VIDEO_START(mariner);
	DECLARE_VIDEO_START(mimonkey);
	DECLARE_VIDEO_START(scorpion);
	DECLARE_VIDEO_START(ad2083);
	DECLARE_VIDEO_START(dambustr);
	DECLARE_VIDEO_START(harem);
	DECLARE_VIDEO_START(bagmanmc);

	uint32_t screen_update_galaxold(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
	uint32_t screen_update_dambustr(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);

	TIMER_CALLBACK_MEMBER(stars_blink_callback);
	TIMER_CALLBACK_MEMBER(stars_scroll_callback);
	TIMER_DEVICE_CALLBACK_MEMBER(galaxold_interrupt_timer);
	uint8_t hunchbkg_intack();

	void state_save_register();
	void video_start_common();
	void pisces_modify_spritecode(uint8_t *spriteram, int *code, int *flipx, int *flipy, int offs);
	void mooncrst_modify_spritecode(uint8_t *spriteram, int *code, int *flipx, int *flipy, int offs);
	void rockclim_draw_background(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
	void rockclim_modify_spritecode(uint8_t *spriteram, int *code, int *flipx, int *flipy, int offs);
	void harem_modify_spritecode(uint8_t *spriteram, int *code, int *flipx, int *flipy, int offs);
	void mooncrst_modify_charcode(uint16_t *code, uint8_t x);
	void pisces_modify_charcode(uint16_t *code, uint8_t x);
	void mimonkey_modify_charcode(uint16_t *code, uint8_t x);
	void mariner_modify_charcode(uint16_t *code, uint8_t x);
	void dambustr_modify_charcode(uint16_t *code, uint8_t x);
	void mshuttle_modify_spritecode(uint8_t *spriteram, int *code, int *flipx, int *flipy, int offs);
	void mimonkey_modify_spritecode(uint8_t *spriteram, int *code, int *flipx, int *flipy, int offs);
	void batman2_modify_spritecode(uint8_t *spriteram, int *code, int *flipx, int *flipy, int offs);
	void dkongjrm_modify_spritecode(uint8_t *spriteram, int *code, int *flipx, int *flipy, int offs);
	void dkongjrmc_modify_spritecode(uint8_t *spriteram, int *code, int *flipx, int *flipy, int offs);
	void ad2083_modify_spritecode(uint8_t *spriteram, int *code, int *flipx, int *flipy, int offs);
	void dambustr_modify_spritecode(uint8_t *spriteram, int *code, int *flipx, int *flipy, int offs);
	void drivfrcg_modify_color(uint8_t *color);
	void galaxold_draw_bullets(bitmap_ind16 &bitmap, const rectangle &cliprect, int offs, int x, int y);
	void scrambold_draw_bullets(bitmap_ind16 &bitmap, const rectangle &cliprect, int offs, int x, int y);
	void darkplnt_draw_bullets(bitmap_ind16 &bitmap, const rectangle &cliprect, int offs, int x, int y);
	void dambustr_draw_bullets(bitmap_ind16 &bitmap, const rectangle &cliprect, int offs, int x, int y);
	void galaxold_draw_background(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
	void scrambold_draw_background(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
	void ad2083_draw_background(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
	void stratgyx_draw_background(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
	void minefld_draw_background(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
	void rescue_draw_background(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
	void mariner_draw_background(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
	void dambustr_draw_background(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
	void dambustr_draw_upper_background(bitmap_ind16 &bitmap, const rectangle &cliprect);
	void galaxold_init_stars(int colors_offset);
	void plot_star(bitmap_ind16 &bitmap, int x, int y, int color, const rectangle &cliprect);
	void noop_draw_stars(bitmap_ind16 &bitmap, const rectangle &cliprect);
	void galaxold_draw_stars(bitmap_ind16 &bitmap, const rectangle &cliprect);
	void scrambold_draw_stars(bitmap_ind16 &bitmap, const rectangle &cliprect);
	void rescue_draw_stars(bitmap_ind16 &bitmap, const rectangle &cliprect);
	void mariner_draw_stars(bitmap_ind16 &bitmap, const rectangle &cliprect);
	void start_stars_blink_timer(double ra, double rb, double c);
	void start_stars_scroll_timer();
	void draw_bullets_common(bitmap_ind16 &bitmap, const rectangle &cliprect);
	void draw_sprites(bitmap_ind16 &bitmap, uint8_t *spriteram, size_t spriteram_size);
	void bagmanmc_modify_charcode(uint16_t *code, uint8_t x);
	void bagmanmc_modify_spritecode(uint8_t *spriteram, int *code, int *flipx, int *flipy, int offs);
	void machine_reset_common(int line);
	void galaxian(machine_config &config);
	void galaxold_base(machine_config &config);
	void ckongg(machine_config &config);
	void _4in1(machine_config &config);
	void bongo(machine_config &config);
	void racknrol(machine_config &config);
	void hunchbkg(machine_config &config);
	void videotron(machine_config &config);
	void hexpoola(machine_config &config);
	void dkongjrm(machine_config &config);
	void tazzmang(machine_config &config);
	void scrambleo(machine_config &config);
	void scrambler(machine_config &config);
	void spcwarp(machine_config &config);
	void dkongjrmc(machine_config &config);
	void bagmanmc(machine_config &config);
	void bullsdrtg(machine_config &config);
	void drivfrcg(machine_config &config);
	void rockclim(machine_config &config);
	void scramblb(machine_config &config);
	void porter(machine_config &config);
	void scramb2(machine_config &config);
	void scramb3(machine_config &config);
	void ozon1(machine_config &config);
	void mooncrst(machine_config &config);
	void guttang(machine_config &config);
	void ckongmc(machine_config &config);
	void galaxian_audio(machine_config &config);
	void mooncrst_audio(machine_config &config);
	void _4in1_map(address_map &map);
	void bagmanmc_map(address_map &map);
	void bongo_map(address_map &map);
	void bongo_io(address_map &map);
	void bullsdrtg_data_map(address_map &map);
	void ckongg_map(address_map &map);
	void ckongmc_map(address_map &map);
	void dkongjrm_map(address_map &map);
	void dkongjrmc_map(address_map &map);
	void drivfrcg_program(address_map &map);
	void drivfrcg_io(address_map &map);
	void galaxold_map(address_map &map);
	void guttang_map(address_map &map);
	void hexpoola_data(address_map &map);
	void hexpoola_io(address_map &map);
	void hunchbkg_map(address_map &map);
	void hunchbkg_data(address_map &map);
	void hustlerb3_map(address_map &map);
	void mooncrst_map(address_map &map);
	void ozon1_io_map(address_map &map);
	void ozon1_map(address_map &map);
	void racknrol_map(address_map &map);
	void racknrol_io(address_map &map);
	void rockclim_map(address_map &map);
	void scramb_common_map(address_map &map);
	void scramb2_map(address_map &map);
	void scramb3_map(address_map &map);
	void scramblb_map(address_map &map);
	void scrambleo_map(address_map &map);
	void scrambler_map(address_map &map);
	void spcwarp_map(address_map &map);
	void tazzmang_map(address_map &map);

protected:
	virtual void machine_start() override { m_leds.resolve(); }
};

#define galaxold_coin_counter_0_w galaxold_coin_counter_w

#endif
