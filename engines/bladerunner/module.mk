MODULE := engines/bladerunner

MODULE_OBJS = \
	actor.o \
	actor_clues.o \
	actor_combat.o \
	actor_dialogue_queue.o \
	actor_walk.o \
	adpcm_decoder.o \
	ambient_sounds.o \
	archive.o \
	aud_stream.o \
	audio_cache.o \
	audio_mixer.o \
	audio_player.o \
	audio_speech.o \
	bladerunner.o \
	boundingbox.o \
	chapters.o \
	combat.o \
	crimes_database.o \
	debugger.o \
	decompress_lcw.o \
	decompress_lzo.o \
	detection.o \
	dialogue_menu.o \
	fog.o \
	font.o \
	game_flags.o \
	game_info.o \
	image.o \
	item.o \
	item_pickup.o \
	items.o \
	light.o \
	lights.o \
	matrix.o \
	mouse.o \
	movement_track.o \
	music.o \
	obstacles.o \
	outtake.o \
	overlays.o \
	regions.o \
	savefile.o \
	scene.o \
	scene_objects.o \
	screen_effects.o \
	script/script.o \
	script/init_script.o \
	script/kia_script.o \
	script/vk_script.o \
	script/esper_script.o \
	script/police_maze.o \
	script/ai_script.o \
	script/ai/answering_machine.o \
	script/ai/baker.o \
	script/ai/blimp_guy.o \
	script/ai/bryant.o \
	script/ai/bullet_bob.o \
	script/ai/chew.o \
	script/ai/clovis.o \
	script/ai/crazylegs.o \
	script/ai/dektora.o \
	script/ai/desk_clerk.o \
	script/ai/dispatcher.o \
	script/ai/early_q.o \
	script/ai/early_q_bartender.o \
	script/ai/fish_dealer.o \
	script/ai/free_slot_a.o \
	script/ai/free_slot_b.o \
	script/ai/gaff.o \
	script/ai/general_doll.o \
	script/ai/generic_walker_a.o \
	script/ai/generic_walker_b.o \
	script/ai/generic_walker_c.o \
	script/ai/gordo.o \
	script/ai/governor_kolvig.o \
	script/ai/grigorian.o \
	script/ai/guzza.o \
	script/ai/hanoi.o \
	script/ai/hasan.o \
	script/ai/hawkers_barkeep.o \
	script/ai/hawkers_parrot.o \
	script/ai/holloway.o \
	script/ai/howie_lee.o \
	script/ai/hysteria_patron1.o \
	script/ai/hysteria_patron2.o \
	script/ai/hysteria_patron3.o \
	script/ai/insect_dealer.o \
	script/ai/isabella.o \
	script/ai/izo.o \
	script/ai/klein.o \
	script/ai/lance.o \
	script/ai/leon.o \
	script/ai/lockup_guard.o \
	script/ai/lucy.o \
	script/ai/luther.o \
	script/ai/maggie.o \
	script/ai/male_announcer.o \
	script/ai/marcus.o \
	script/ai/mccoy.o \
	script/ai/mia.o \
	script/ai/moraji.o \
	script/ai/murray.o \
	script/ai/mutant1.o \
	script/ai/mutant2.o \
	script/ai/mutant3.o \
	script/ai/newscaster.o \
	script/ai/officer_grayford.o \
	script/ai/officer_leary.o \
	script/ai/photographer.o \
	script/ai/rachael.o \
	script/ai/rajif.o \
	script/ai/runciter.o \
	script/ai/sadik.o \
	script/ai/sebastian.o \
	script/ai/sergeant_walls.o \
	script/ai/shoeshine_man.o \
	script/ai/steele.o \
	script/ai/taffy.o \
	script/ai/taffy_patron.o \
	script/ai/teenager.o \
	script/ai/the_bard.o \
	script/ai/transient.o \
	script/ai/tyrell.o \
	script/ai/tyrell_guard.o \
	script/ai/zuben.o \
	script/scene_script.o \
	script/scene/ar01.o \
	script/scene/ar02.o \
	script/scene/bb01.o \
	script/scene/bb02.o \
	script/scene/bb03.o \
	script/scene/bb04.o \
	script/scene/bb05.o \
	script/scene/bb06.o \
	script/scene/bb07.o \
	script/scene/bb08.o \
	script/scene/bb09.o \
	script/scene/bb10.o \
	script/scene/bb11.o \
	script/scene/bb12.o \
	script/scene/bb51.o \
	script/scene/ct01.o \
	script/scene/ct02.o \
	script/scene/ct03.o \
	script/scene/ct04.o \
	script/scene/ct05.o \
	script/scene/ct06.o \
	script/scene/ct07.o \
	script/scene/ct08.o \
	script/scene/ct09.o \
	script/scene/ct10.o \
	script/scene/ct11.o \
	script/scene/ct12.o \
	script/scene/ct51.o \
	script/scene/dr01.o \
	script/scene/dr02.o \
	script/scene/dr03.o \
	script/scene/dr04.o \
	script/scene/dr05.o \
	script/scene/dr06.o \
	script/scene/hc01.o \
	script/scene/hc02.o \
	script/scene/hc03.o \
	script/scene/hc04.o \
	script/scene/hf01.o \
	script/scene/hf02.o \
	script/scene/hf03.o \
	script/scene/hf04.o \
	script/scene/hf05.o \
	script/scene/hf06.o \
	script/scene/hf07.o \
	script/scene/kp01.o \
	script/scene/kp02.o \
	script/scene/kp03.o \
	script/scene/kp04.o \
	script/scene/kp05.o \
	script/scene/kp06.o \
	script/scene/kp07.o \
	script/scene/ma01.o \
	script/scene/ma02.o \
	script/scene/ma04.o \
	script/scene/ma05.o \
	script/scene/ma06.o \
	script/scene/ma07.o \
	script/scene/ma08.o \
	script/scene/nr01.o \
	script/scene/nr02.o \
	script/scene/nr03.o \
	script/scene/nr04.o \
	script/scene/nr05.o \
	script/scene/nr06.o \
	script/scene/nr07.o \
	script/scene/nr08.o \
	script/scene/nr09.o \
	script/scene/nr10.o \
	script/scene/nr11.o \
	script/scene/ps01.o \
	script/scene/ps02.o \
	script/scene/ps03.o \
	script/scene/ps04.o \
	script/scene/ps05.o \
	script/scene/ps06.o \
	script/scene/ps07.o \
	script/scene/ps09.o \
	script/scene/ps10.o \
	script/scene/ps11.o \
	script/scene/ps12.o \
	script/scene/ps13.o \
	script/scene/ps14.o \
	script/scene/ps15.o \
	script/scene/rc01.o \
	script/scene/rc02.o \
	script/scene/rc03.o \
	script/scene/rc04.o \
	script/scene/rc51.o \
	script/scene/tb02.o \
	script/scene/tb03.o \
	script/scene/tb05.o \
	script/scene/tb06.o \
	script/scene/tb07.o \
	script/scene/ug01.o \
	script/scene/ug02.o \
	script/scene/ug03.o \
	script/scene/ug04.o \
	script/scene/ug05.o \
	script/scene/ug06.o \
	script/scene/ug07.o \
	script/scene/ug08.o \
	script/scene/ug09.o \
	script/scene/ug10.o \
	script/scene/ug12.o \
	script/scene/ug13.o \
	script/scene/ug14.o \
	script/scene/ug15.o \
	script/scene/ug16.o \
	script/scene/ug17.o \
	script/scene/ug18.o \
	script/scene/ug19.o \
	set.o \
	settings.o \
	set_effects.o \
	shape.o \
	slice_animations.o \
	slice_renderer.o \
	subtitles.o \
	suspects_database.o \
	text_resource.o \
	time.o \
	ui/elevator.o \
	ui/end_credits.o \
	ui/esper.o \
	ui/kia.o \
	ui/kia_log.o \
	ui/kia_section_base.o \
	ui/kia_section_clues.o \
	ui/kia_section_crimes.o \
	ui/kia_section_diagnostic.o \
	ui/kia_section_help.o \
	ui/kia_section_load.o \
	ui/kia_section_pogo.o \
	ui/kia_section_save.o \
	ui/kia_section_settings.o \
	ui/kia_section_suspects.o \
	ui/kia_shapes.o \
	ui/scores.o \
	ui/spinner.o \
	ui/ui_check_box.o \
	ui/ui_container.o \
	ui/ui_image_picker.o \
	ui/ui_input_box.o \
	ui/ui_scroll_box.o \
	ui/ui_slider.o \
	ui/vk.o \
	view.o \
	vqa_decoder.o \
	vqa_player.o \
	waypoints.o \
	zbuffer.o

# This module can be built as a plugin
ifeq ($(ENABLE_BLADERUNNER), DYNAMIC_PLUGIN)
PLUGIN := 1
endif

# Include common rules
include $(srcdir)/rules.mk
