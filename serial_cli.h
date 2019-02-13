#pragma once

#include "constants.h"
#include "mqtt8622.h"

int cmd_help();
int cmd_led();
int cmd_exit();

void cli_init();
void my_cli();

void help_help();
void help_led();
void help_exit();

void read_line();
void parse_line();
int execute();


