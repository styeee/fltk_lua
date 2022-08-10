#include <lua.hpp>

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Text_Editor.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_File_Chooser.H>

struct form
{
    int x;int y;int w;int h;

    inline
    void border(int b)
    {x+=b;y+=b;b<<=1;w-=b;h-=b;}

    form&&ver_div(const int c,const int dist=0)
    {
        h-=(c+dist);
        return form{x,y+h+dist,w,c};
    }

    form&&gor_div(const int c,const int dist=0)
    {
        w-=(c+dist);
        return form{x+w+dist,y,c,h};
    }
};
#define un(s) s.x,s.y,s.w,s.h

Fl_Text_Buffer text;

int main()
{
	lua_State*l=luaL_newstate();
	luaL_openlibs(l);

    form gen{0,0,800,600};

    Fl_Window win(gen.w,gen.h,"lua editor with FLTK");

    gen.border(20);
    
    const short height=50;
    form&&zone_bottom=gen.ver_div(height,10);
    form&&zone_left=gen.ver_div(height,10);
    form&&zone_right=zone_left.gor_div(zone_left.w>>1,10);

    Fl_Text_Editor edit(un(gen));
    Fl_Button run(un(zone_bottom),"run!");
    run.callback([](Fl_Widget*s,void*d)
    {
        luaL_dostring((lua_State*)d,text.text());
    },l);

    Fl_Button load(un(zone_left),"load");
    load.callback([](Fl_Widget*s,void*d)
    {
        const char*file=fl_file_chooser("select .lua","*.lua","test.lua");
        if(!file)return;
        text.loadfile(file);
    },l);

    Fl_Button save(un(zone_right),"save");
    save.callback([](Fl_Widget*s,void*d)
    {
        const char*file=fl_file_chooser("enter .lua","*.lua","test.lua");
        text.savefile(file);
    },l);
    
    edit.buffer(text);
    win.resizable(edit);
    win.show();

	return Fl::run();
}