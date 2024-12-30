#include <screen.h>
#include <context.h>
#include <general_config.h>

int main()
{
    ::screen::ScreenContext context { CONFIG_DIR"/config.cfg" };
    ::screen::Screen scr { context };
    scr.run();
	return 0;
}
