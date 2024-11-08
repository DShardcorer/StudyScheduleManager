#include <stdio.h>
#include <string.h>
#include "interface.h"



void displayLogoAndMenu() {
    // ASCII Logo
    printf(" .oooooo..o     .                     .o8                    .oooooo..o           oooo                        .o8              oooo            \n");
    printf("d8P'    `Y8   .o8                    \"888                   d8P'    `Y8           `888                       \"888              `888            \n");
    printf("Y88bo.      .o888oo oooo  oooo   .oooo888  oooo    ooo      Y88bo.       .ooooo.   888 .oo.    .ooooo.   .oooo888  oooo  oooo   888   .ooooo.  \n");
    printf(" `\"Y8888o.    888   `888  `888  d88' `888   `88.  .8'        `\"Y8888o.  d88' `\"Y8  888P\"Y88b  d88' `88b d88' `888  `888  `888   888  d88' `88b \n");
    printf("     `\"Y88b   888    888   888  888   888    `88..8'             `\"Y88b 888        888   888  888ooo888 888   888   888   888   888  888ooo888 \n");
    printf("oo     .d8P   888 .  888   888  888   888     `888'         oo     .d8P 888   .o8  888   888  888    .o 888   888   888   888   888  888    .o \n");
    printf("8\"\"88888P'    \"888\"  `V88V\"V8P' `Y8bod88P\"     .8'          8\"\"88888P'  `Y8bod8P' o888o o888o `Y8bod8P' `Y8bod88P\"  `V88V\"V8P' o888o `Y8bod8P' \n");
    printf("                                           .o..P'                                                                                             \n");
    printf("                                           `Y8P'                                                                                              \n");
    printf("\n");
    printf("                              ooo        ooooo                                                                                               \n");
    printf("                              `88.       .888'                                                                                               \n");
    printf("                               888b     d'888   .oooo.   ooo. .oo.    .oooo.    .oooooooo  .ooooo.  oooo d8b                                \n");
    printf("                               8 Y88. .P  888  `P  )88b  `888P\"Y88b  `P  )88b  888' `88b  d88' `88b `888\"\"8P                                \n");
    printf("                               8  `888'   888   .oP\"888   888   888   .oP\"888  888   888  888ooo888  888                                    \n");
    printf("                               8    Y     888  d8(  888   888   888  d8(  888  `88bod8P'  888    .o  888                                    \n");
    printf("                              o8o        o888o `Y888\"\"8o o888o o888o `Y888\"\"8o `8oooooo.  `Y8bod8P' d888b                                   \n");
    printf("                                                                               d\"     YD                                                    \n");
    printf("                                                                               \"Y88888P'                                                    \n");

    // Instructions menu
    printf("===================================================================\n");
    printf("Instructions:\n");
    printf("1. Enter 'ALL' to view the entire weekly schedule.\n");
    printf("2. Enter a specific day to view the schedule for that day (e.g., 'Monday').\n");
    printf("3. Enter 'EXIT' to quit the program.\n");
    printf("===================================================================\n");
    printf("\n");
}