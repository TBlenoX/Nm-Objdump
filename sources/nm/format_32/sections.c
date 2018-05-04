/*
** EPITECH PROJECT, 2018
** sections.c
** File description:
** Created by Thomas BLENEAU
*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <elf.h>
#include <sys/mman.h>
#include "nm.h"

static const char SYM_TAB[] = {'.', 's', 'y', 'm', 't', 'a', 'b', '\0'};

static const char STR_TAB[] = {'.', 's', 't', 'r', 't', 'a', 'b', '\0'};

elf_sym_t *elf32_sections(Elf32_Ehdr *elfH_32, Elf32_Shdr *elf_S)
{
	size_t inc = 0;
	size_t index = 0;
	char *string = (char *) ((void *) elfH_32 +
				elf_S[elfH_32->e_shstrndx].sh_offset);
	char *cmp = NULL;
	char *str_tab = NULL;
	Elf32_Sym *symbls = NULL;

	for (inc = 0; inc < elfH_32->e_shnum; inc++) {
		cmp = string + elf_S[inc].sh_name;
		if (!strcmp(cmp, SYM_TAB)) {
			index = inc;
			symbls = (Elf32_Sym *)
				((void *) elfH_32 + (elf_S + inc)->sh_offset);
		} else if (!strcmp(cmp, STR_TAB))
			str_tab = (char *) ((void *) elfH_32 +
						(elf_S + inc)->sh_offset);
	}
	return (elf32_symbols(symbls, index, str_tab, elf_S));
}
