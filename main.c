#include "cub3d.h"

void draw_line(t_game *game, int x1, int y1, int x2, int y2, int color) 
{ 
	int dx;
	int dy;
	dx = abs(x2 - x1);
	dy = abs(y2 - y1);
	int err2;
	int sign_x;
	int sign_y;

	if (x1 < x2)
		sign_x = 1;
	else
		sign_x = -1;
	if (y1 < y2)
		sign_y = 1;
	else
		sign_y = -1;
	int err;
	err = dx - dy;

	//mlx_put_pixel(game->img, x2, y2, color);

	while (x1 != x2 || y1 != y2) {
		if ((x1 >= 0 && x1 <= WIGHT) && (y1 >= 0 && y1 <= HEIGHT))
			mlx_put_pixel(game->img, x1, y1, color);
		err2 = 2 * err;

		if (err2 > -dy) {
			err -= dy;
			x1 += sign_x;
		}

		if (err2 < dx) {
			err += dx;
			y1 += sign_y;
		}
	}
}

void set_game(t_game  *game, char **av)
{
	game->player = malloc (sizeof(t_player));

	name_check(av[1]);
	// game->cub->maplines = maplines(av[1]);
	// game->cub->i = 0;
	// game->cub->j = 0;

	game->maps = mapreader(av[1]);
	// check_the_path(game->maps, game->cub);
	// check_the_path_2(game->maps, game->cub);
	// check_component(game->maps);

	game->height = 8;
	game->width = 8;

	game->player->x = 100;
	game->player->y = 100;
	game->player->angle = 0;
}

int valide_move(int tmpy,int tmpx,t_game *game)
{
	tmpy /= 64;
	tmpx /= 64;
	if (game->maps[tmpy][tmpx] == '1')
		return 0;
	return 1;
}

void key_press(void *game2)
{
	t_game *game = (t_game *)game2;
	int speed = 2;
	float tmpx = game->player->x;
	float tmpy = game->player->y;

	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx);
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
		game->player->angle -= 0.087266;
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
		game->player->angle += 0.087266;
	if (game->player->angle < 0)
		game->player->angle += 2 * M_PI;
	if (game->player->angle > 2 * M_PI)
		game->player->angle -= 2 * M_PI;
	

	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
	{
		tmpy += speed * sin(game->player->angle + M_PI / 2);
		tmpx += speed * cos(game->player->angle + M_PI / 2);
		if (valide_move(tmpy,tmpx,game))
		{
			game->player->x = tmpx;
			game->player->y = tmpy;
		}
	}
	
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
	{
		tmpy -= speed * sin(game->player->angle + M_PI / 2);
		tmpx -= speed * cos(game->player->angle + M_PI / 2);
		if (valide_move(tmpy,tmpx,game))
		{
			game->player->x = tmpx;
			game->player->y = tmpy;
		}
	}

	if (mlx_is_key_down(game->mlx, MLX_KEY_W) || mlx_is_key_down(game->mlx, MLX_KEY_UP))
	{
		tmpy +=  speed * sin(game->player->angle);
		tmpx +=  speed * cos(game->player->angle);
		if (valide_move(tmpy,tmpx,game))
		{
			game->player->x = tmpx;
			game->player->y = tmpy;
		}
	}
	
	if (mlx_is_key_down(game->mlx, MLX_KEY_S) || mlx_is_key_down(game->mlx, MLX_KEY_DOWN))
	{
		tmpy -= speed * sin(game->player->angle);
		tmpx -= speed * cos(game->player->angle);
		if (valide_move(tmpy,tmpx,game))
		{
			game->player->x = tmpx;
			game->player->y = tmpy;
		}
	}
	

}

void draw_rectangle(mlx_image_t* img, int x, int y, int width,int color)
{
	int i = 0;
	int j ;

	while (i < width)
	{
		j = 0;
		while (j < width)
		{
			mlx_put_pixel(img, x + i, y + j, color);
			j++;
		}
		i++;
	}
}


void draw(void *game2)
{
	t_game *game = (t_game *)game2;

	ray_casting(game);
}


int main(int ac, char **av)
{
	t_game  *game;


	if (ac == 2)
	{
		game = malloc(sizeof(t_game));
		set_game(game, av);


		game->mlx = mlx_init(WIGHT, HEIGHT, "Cub3d", false);
		game->img = mlx_new_image(game->mlx, WIGHT, HEIGHT);
		mlx_image_to_window(game->mlx,game->img,0,0);
		// mlx_key_hook(game->mlx, &key_press, game);

		mlx_loop_hook(game->mlx, key_press, game);
		mlx_loop_hook(game->mlx, draw, game);

		mlx_loop(game->mlx);
		
	}
	return (0);
}