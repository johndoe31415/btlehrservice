/*
 *   This file was AUTO-GENERATED by pypgmopts.
 *
 *   https://github.com/johndoe31415/pypgmopts
 *
 *   Do not edit it by hand, your changes will be overwritten.
 *
 *   Generated at: 2020-07-11 17:33:03
 */

#ifndef __ARGPARSE_H__
#define __ARGPARSE_H__

#include <stdbool.h>

#define ARGPARSE_DEFAULT_VERBOSE		0

#define ARGPARSE_NO_OPTION		0
#define ARGPARSE_POSITIONAL_ARG	1

enum argparse_option_t {
	ARG_RANDOM_BTLE_ADDRESS = 2,
	ARG_USER = 3,
	ARG_CHOWN = 4,
	ARG_VERBOSE = 5,
	ARG_DESTINATION_ADDRESS = 6,
	ARG_UNIX_SOCKET = 7,
};

typedef void (*argparse_errmsg_callback_t)(const char *errmsg, ...);
typedef void (*argparse_errmsg_option_callback_t)(enum argparse_option_t error_option, const char *errmsg, ...);
typedef bool (*argparse_callback_t)(enum argparse_option_t option, const char *value, argparse_errmsg_callback_t errmsg_callback);
typedef bool (*argparse_plausibilization_callback_t)(argparse_errmsg_option_callback_t errmsg_callback);

bool argparse_parse(int argc, char **argv, argparse_callback_t argument_callback, argparse_plausibilization_callback_t plausibilization_callback);
void argparse_show_syntax(void);
void argparse_parse_or_quit(int argc, char **argv, argparse_callback_t argument_callback, argparse_plausibilization_callback_t plausibilization_callback);

#endif
