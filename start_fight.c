#include "corewar.h"
#include "ncurs.h"

void    ft_get_n_car_value(t_core *core, t_champ *champ)
{
    if (core->arena[champ->cars->pos % MEM_SIZE] > 0 && core->arena[champ->cars->pos % MEM_SIZE] < 16)
    {
        champ->cars->opcode = core->arena[champ->cars->pos % MEM_SIZE];
        champ->cars->cycle = op_tab[champ->cars->opcode - 1].cycle;;
    }
    else
        champ->cars->opcode = 0;
}

void    ft_touch_car(t_core *core, t_champ *champ)
{
    if (champ->cars->cycle < 2) {
        champ->cars->cycle = 0;
        if (champ->cars->opcode > 0 && champ->cars->opcode < 16)
            ft_opcode_switcher(core, champ);
        else
            champ->cars->pos++;
        ft_get_n_car_value(core, champ);
    }
    else
        champ->cars->cycle--;
}

void    ft_start_fight(t_core *core) {
    t_champ *tmp;
    do_ncurs(core);
    getch();
    while (core->c_to_die > 0 && core->qt_car > 0) {
//        ft_dump(core);
//		do_ncurs(core);
        while (tmp)
        {
            if (tmp->cars)
                ft_touch_car(core, tmp);
            tmp = tmp->next;
        }
        tmp = core->champs;
        core->cycle++;
        if (core->cycle == core->c_to_die + core->last_check) {
            ft_make_check(core);
            core->last_check = core->cycle;
        }
    }
}
