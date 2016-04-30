#include "my_printf.h"

int find(t_main *main, char tofind)
{
	int i;

	i = 0;
	while(main->parsed[i] != '\0')
	{
		if(main->parsed[i] == tofind)
			return(1);
		i++;
	}
	return(0);
}

void first(t_main *main)
{
	if(find(main, 'x') == 1 || find(main, 'X') == 1)
			{
					if(main->dietat == 1 && (unsigned long long int)main->elem != 0 && find(main, 'x') == 1)
						main->print = ft_strjoin("0x",main->print);
					else if(main->dietat == 1 && (unsigned long long int)main->elem != 0 && find(main, 'X') == 1)
						main->print = ft_strjoin("0X",main->print);
			}
}

void last_mini(t_main *main)
{
	if(main->plusetat == 1)
		main->print = ft_strjoin("+", main->print);
	if(main->dietat == 1 && (unsigned long long int)main->elem != 0 && main->zeroetat == 1 && find(main, 'x') == 1)
		main->print = ft_strjoin("0x",main->print);
	if(find(main,'c') == 1 && main->width > 0)
	{
		if((int)main->elem == 0)
		{
			int i;
			main->print = ft_memalloc(sizeof(char) * 10);
			i = 1;
			while(i < main->width)
			{
				if(main->zeroetat == 1)
					main->print = ft_strjoin(main->print, "0");
				else
					main->print = ft_strjoin(main->print, " ");
				i++;
			}
			main->casc = 1;
		}
	}	
}

void one_else(t_main *main, int needzero)
{
if(find(main, 'o') == 0 && (find(main, 'd') == 0 && find(main, '-') == 0 ))
				{
					while(needzero > 0)
					{
						main->print = ft_strjoin(main->print, "0");
						main->size++;
						needzero--;
					}
				}
				else
				{
					while(needzero > 0)
					{
						main->print = ft_strjoin(main->print, " ");
						main->size++;
						needzero--;
					}
				}
}

void ok_ok(t_main *main, int needzero)
{
		if(needzero < 0)
				{
					main->width = -main->width;
					needzero = main->width - main->size;
				}
				while(needzero > 0)
				{

					main->print = ft_strjoin(main->print, " ");
					main->size++;
					needzero--;
				}
}



void another_else(t_main *main, int needzero)
{
		int i = 0;
					int i2 = 0;
					char *temp;
					temp = (char *)malloc(sizeof(char) * ft_strlen(main->print) + 10);
					while(main->print[i] != '\0')
					{
						if(main->print[i] != '-')
						{
							temp[i2] = main->print[i];
							i2++;
						}
						i++;
					}
					temp[i2] = '\0';
					main->print = temp;
					while(needzero > 0)
					{
		
						main->print = ft_strjoin("0", main->print);
						main->size++;
						needzero--;
					}
					main->print = ft_strjoin("-", main->print);
}

void ok_its_norme(t_main *main, int needzero)
{
	if(main->moinetat == 0)
			{
				if(main->signemoin != 1)
				{
					while(needzero > 0)
					{
						if(find(main,' ') == 0)
						{
							if(find(main,'p') == 0)
								main->print = ft_strjoin("0", main->print);
						}
						else
							main->print = ft_strjoin(main->print,"0");
						main->size++;
						needzero--;
					}
				}
				else
					another_else(main, needzero);
			}
			else
				one_else(main, needzero);
}

void in_nor(t_main *main)
{
		if(find(main,'s') == 1 && main->width >0 && main->zeroetat == 1)
								main->print = ft_strjoin("0", main->print);
							else
							{
								if(main->zeroetat == 1 && no_conv(main) == 1 && main->width > 0)
									main->print = ft_strjoin("0", main->print);
								else if(main->zeroetat == 1 && main->width > 0 && main->accurate <= 0)
									main->print = ft_strjoin("0", main->print);
								else
									main->print = ft_strjoin(" ", main->print);
							}
}

void hai_hai(t_main *main, int needzero)
{
	if(main->plusetat == 1)
					{
						main->plusetat = 0;
						main->print = ft_strjoin("+", main->print);
					}
				while(needzero > 0)
				{
					if(find(main,'c') == 1&& find(main,'.') == 1)
						main->print = ft_strjoin(" ", main->print);
					else
					{
						if(main->zeroetat == 1 && main->accurate < 0)
							main->print = ft_strjoin("0", main->print);
						else
							in_nor(main);
					}
					main->size++;
					needzero--;
				}
}

int add_mini(t_main *main)
{
	int needzero;
	int ok;

	ok = 0;
	needzero = main->width - main->size;
	if(main->stop == 1)
		return(0);
	if(needzero > 0 || needzero < 0)
	{   
		if(main->zeroetat == 0 || main->pointetat != 0)
		{
			first(main);
			if(main->moinetat == 0)
				hai_hai(main,needzero);
			else
				ok_ok(main,needzero);
		}
		else 
			ok_its_norme(main,needzero);
	}
	last_mini(main);
	return (0);
}



int okorno(t_main *main)
{
	int i;

	i = 0;
	if(main->parsed[i] == '+' || main->parsed[i] == '-' || main->parsed[i] == '#' || main->parsed[i] == ' ')
	{
		i++;
	}
	while(main->parsed[i] <= '9' && main->parsed[i] >= '0')
	{
		i++;
	}
	if(main->parsed[i] == '*')
		return(1);
	return(0);
}

void first_width(t_main *main)
{
	int size;
	int i;
	int i2;
	char *myacc;

		i2 = 0;
		i = main->i + 1;
		if(main->chaine[main->i + 1] == '0')
		{
			main->zeroetat = 1;
			main->i++;
		}  
		while(main->chaine[main->i + 1] >= '0' && main->chaine[main->i + 1] <= '9')
		{
			main->i++;
		}
		size = main->i - i;
		myacc = (char *)malloc(sizeof(char) * size + 10);
		while(i <= main->i)
		{
			myacc[i2] = main->chaine[i];
			i2++;
			i++;
		}
		myacc[i2] = '\0';
		main->width = ft_atoi(myacc);
}

int my_width(t_main *main, va_list *myva)
{
	int yesno;

	yesno = okorno(main);
	if(main->etoile == 1)
		yesno = 0;
	if(yesno == 1)
	{	
		while(main->chaine[main->i + 1] != '*')
		{
			main->i++;
		}
	}
	if(main->chaine[main->i + 1] >= '0' && main->chaine[main->i + 1] <= '9' && yesno == 0)
	{
		first_width(main);
	}
	else if(main->chaine[main->i + 1] == '*')
	{
		main->i++;
		main->width = (int)main->elem;
		if(main->width < 0)
			main->moinetat = 1;
		main->elem = va_arg(*myva, void *);
	}
	return (0);
}
