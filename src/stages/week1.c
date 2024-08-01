/*
  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.
*/

#include "week1.h"

#include "psx/archive.h"
#include "psx/mem.h"
#include "fonts/font.h"
int lyrics_select;
//Stage background structure
typedef struct
{
	//Stage background base structure
	StageBack back;
	
	//Textures
	Gfx_Tex tex_back0; //Stage and back
	Gfx_Tex tex_back1; //Curtains
} Back_Week1;
void Back_Week1_DrawFG()
{
	if (stage.song_step >=16 && stage.song_step <=30)
	{
		RECT tline = {0, 16, 320, 1};
		Gfx_DrawRect(&tline, 255, 255, 255);
		
		RECT Top_bar = {0, 0, 320, 16};
	       	Gfx_BlendRect(&Top_bar, 0, 0, 0, 0);
	       	
	       	RECT bline = {0, 224, 320, 1};
		Gfx_DrawRect(&bline, 255, 255, 255);
		
	       	RECT Bottom_bar = {0, 224, 320, 16};
	       	Gfx_BlendRect(&Bottom_bar, 0, 0, 0, 0);
       	}
}
//Stage functions
void Back_Week1_Tick(StageBack *back)
{
	//Back_Week1 *this = (Back_Week1*)back;
	(void)back; //Only for remove warning
	
	struct
	{
              const char *Lyrics;
	} song_lyrics[] = {
	      {" "},
    	  {"ILL MAKE"},
	      {"YOU SAY"},
	      {"HOW PROUD"},
	      {"YOU ARE OF"},
	      {"YOU ARE OF ME"},
	      {"SO"},
	      {"SO STAY"},
	      {"AWAKE"},
	      {"JUST"},
	      {"JUST LONG"},
	      {"ENOUGH TO SEE"},
	      {"MY WAY"},
	};
	if(stage.stage_id == StageId_Bopeebo)
	{
		switch (stage.song_step)
		{
			case 0:
				lyrics_select=0; 
				break;
			case 3368:
				lyrics_select=1;
				break;
			case 3400:
				lyrics_select=2;
				break;
			case 3432:
				lyrics_select=3;
				break;
			case 3478:
				lyrics_select=4;
				break;
			case 3484:
				lyrics_select=5;
				break;
			case 3495:
				lyrics_select=6;
				break;
			case 3507:
				lyrics_select=7;
				break;
			case 3528:
				lyrics_select=8;
				break;
			case 3561:
				lyrics_select=9;
				break;
			case 3568:
				lyrics_select=10;
				break;
			case 3592:
				lyrics_select=11;
				break;
			case 3623:
				lyrics_select=12;
				break;
			case 3807:
				lyrics_select=0;
				break;
		}
	}
	font_bold.draw_col(&font_bold, song_lyrics[lyrics_select].Lyrics, 160, 180, FontAlign_Center, 202 >> 1, 172 >> 1, 61 >> 1);
		
}

void Back_Week1_DrawBG(StageBack *back)
{
	Back_Week1 *this = (Back_Week1*)back;
	
	fixed_t fx, fy, fscroll;

	//Draw curtains
	fscroll = FIXED_DEC(12,10);

	fx = FIXED_MUL(stage.camera.x, fscroll);
	fy = FIXED_MUL(stage.camera.y, fscroll);
	
	RECT curtainl_src = {0, 0, 107, 221};
	RECT_FIXED curtainl_dst = {
		FIXED_DEC(-250,1) - fx,
		FIXED_DEC(-150,1) - fy,
		FIXED_DEC(107,1),
		FIXED_DEC(221,1)
	};
	RECT curtainr_src = {122, 0, 133, 255};
	RECT_FIXED curtainr_dst = {
		FIXED_DEC(110,1) - fx,
		FIXED_DEC(-150,1) - fy,
		FIXED_DEC(134,1),
		FIXED_DEC(255,1)
	};
	
	Stage_DrawTex(&this->tex_back1, &curtainl_src, &curtainl_dst, stage.camera.bzoom);
	Stage_DrawTex(&this->tex_back1, &curtainr_src, &curtainr_dst, stage.camera.bzoom);

	fx = stage.camera.x;
	fy = stage.camera.y;
	
	//Draw Stage
	RECT stage_src = {0, 0, 255, 59};
	RECT_FIXED stage_dst = {
		FIXED_DEC(-230,1) - fx,
		FIXED_DEC(50,1) - fy,
		FIXED_DEC(410,1),
		FIXED_DEC(123,1)
	};

	Debug_MoveTexture(&stage_dst, 1, "stage", 0, 0);
	
	Stage_DrawTex(&this->tex_back0, &stage_src, &stage_dst, stage.camera.bzoom);
	
	//Draw back
	fx = stage.camera.x / 2;
	fy = stage.camera.y / 2;
	
	RECT backl_src = {0, 59, 121, 105};
	RECT_FIXED backl_dst = {
		FIXED_DEC(-190,1) - fx,
		FIXED_DEC(-100,1) - fy,
		FIXED_DEC(121,1),
		FIXED_DEC(105,1)
	};

	Debug_MoveTexture(&backl_dst, 0, "back left", fx, fy);
	RECT backr_src = {120, 59, 135, 120};
	RECT_FIXED backr_dst = {
		FIXED_DEC(60,1) - fx,
		FIXED_DEC(-110,1) - fy,
		FIXED_DEC(136,1),
		FIXED_DEC(120,1)
	};
	RECT backf_src = {0, 59, 1, 1};
	RECT backf_dst = {
		0,
		0,
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
	};
	
	Stage_DrawTex(&this->tex_back0, &backl_src, &backl_dst, stage.camera.bzoom);
	Stage_DrawTex(&this->tex_back0, &backr_src, &backr_dst, stage.camera.bzoom);
	Gfx_DrawTex(&this->tex_back0, &backf_src, &backf_dst);
}

void Back_Week1_Free(StageBack *back)
{
	Back_Week1 *this = (Back_Week1*)back;
	
	//Free structure
	Mem_Free(this);
}

StageBack *Back_Week1_New(void)
{
	//Allocate background structure
	Back_Week1 *this = (Back_Week1*)Mem_Alloc(sizeof(Back_Week1));
	if (this == NULL)
		return NULL;
	
	//Set background functions
	this->back.tick = Back_Week1_Tick;
	this->back.draw_fg = Back_Week1_DrawFG;
	this->back.draw_md = NULL;
	this->back.draw_bg = Back_Week1_DrawBG;
	this->back.free = Back_Week1_Free;
	
	//Load background textures
	IO_Data arc_back = IO_Read("\\WEEK1\\BACK.ARC;1");
	Gfx_LoadTex(&this->tex_back0, Archive_Find(arc_back, "back0.tim"), 0);
	Gfx_LoadTex(&this->tex_back1, Archive_Find(arc_back, "back1.tim"), 0);
	Mem_Free(arc_back);
	
	return (StageBack*)this;
}
