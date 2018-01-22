#include "IA.h"

IA::IA(CaseTerrain** Terrain)
{
	this->Terrain = Terrain;

	Pheromone_Table = new Pheromone*[_nb_case_w];
	for (int i = 0; i < _nb_case_w; i++)
	{
		Pheromone_Table[i] = new Pheromone[_nb_case_h];
	}

};

void IA::deplacement()
{
	x += (speed * dx);
	y += (speed * dy);
};

void IA::analyse()
{
	int cx = -1, cy = -1;

	case_x = (int)x, case_y = (int)y;

	int min_x = ((int)(x - detection_range))<0 ? 0 : ((int)(x - detection_range));
	int max_x = ((int)(x + detection_range)) >= _nb_case_w ? _nb_case_w : ((int)(x + detection_range));
	int min_y = ((int)(y - detection_range))<0 ? 0 : ((int)(y - detection_range));
	int max_y = ((int)(y + detection_range)) >= _nb_case_h ? _nb_case_h : ((int)(y + detection_range));
	
	//analise du terrain et change la direction ou la destination en fonction du resulta
	for (int i = min_x; i < max_x; i++)
	{
		for (int j = min_y; j < max_y; j++)
		{
			switch (destination)
			{
			case IA::home:
				if (Terrain[i][j].Type == CaseTerrain::TypeTerrain::Base)
				{
					if (case_x == cx && case_y == cy)
					{
						change_dest();
						contenue = none;
						cx = -1, cy = -1;
					}
					else
					{
						cx = i;
						cy = j;
					}
				}
				break;
			case IA::food:
				if (Terrain[i][j].Type == CaseTerrain::TypeTerrain::Nourriture)
				{
					if (case_x == cx && case_y == cy)
					{
						change_dest();
						contenue = food;
						cx = -1, cy = -1;
					}
					else
					{
						cx = i;
						cy = j;
					}
				}
				break;
			case IA::water:
				if (Terrain[i][j].Type == CaseTerrain::TypeTerrain::Eau)
				{
					if (case_x == cx && case_y == cy)
					{
						change_dest();
						contenue = water;
						cx = -1, cy = -1;
					}
					else
					{
						cx = i;
						cy = j;
					}
				}
				break;
			case IA::enemy:
				if (Terrain[i][j].Type == CaseTerrain::TypeTerrain::Base)
				{
					if (case_x == cx && case_y == cy)
					{
						contenue = enemy;
						change_dest();
						cx = -1, cy = -1;
					}
					else
					{
						cx = i;
						cy = j;
					}
				}
				break;
			case IA::search:
				if (Terrain[i][j].Type == CaseTerrain::TypeTerrain::Nourriture || Terrain[i][j].Type == CaseTerrain::TypeTerrain::Eau)
				{
					if (case_x == cx && case_y == cy)
					{
						change_dest();
						cx = -1, cy = -1;
					}
					else
					{
						if (cx < 0)
						{
							cx = i;
							cy = j;
						}
						else
						{
							if ((abs(x - cx) + abs(y - cy)) / 2.0 > (abs(x - i) + abs(y - j)) / 2.0)
							{
								cx = i;
								cy = j;
							}
						}
					}
				}
				/*if (Terrain[i][j].Type == CaseTerrain::TypeTerrain::Base)
				{
					if (case_x == cx && case_y == cy)
					{
						change_dest();
						cx = -1, cy = -1;
					}
					else
					{
						if (cx < 0)
						{
							cx = i;
							cy = j;
						}
						else
						{
							if ((abs(x - cx) + abs(y - cy)) / 2.0 >(abs(x - i) + abs(y - j)) / 2.0)
							{
								cx = i;
								cy = j;
							}
						}
					}
				}//*/
				break;
			}
		}
	}

	//suit les pheromones si aucune direction n'est prise

	if (cx < 0)
	{
		Pheromone::Type searched;
		switch (destination)
		{
		case IA::home:
			searched = Pheromone::Type::home;
			break;
		case IA::food:
			searched = Pheromone::Type::food;
			break;
		case IA::water:
			searched = Pheromone::Type::water;
			break;
		case IA::enemy:
			searched = Pheromone::Type::enemy;
			break;
		default:
			searched = Pheromone::Type::none;
			break;
		}

		if (searched != Pheromone::Type::none)
		{
			for (int i = min_x; i < max_x; i++)
			{
				for (int j = min_y; j < max_y; j++)
				{
					float value = 0;
					float& valuec = Pheromone_Table[i][j][searched];
					
					if (valuec > 0)
					{
						if (value < valuec)
						{
							cx = i;
							cy = j;
						}
						else if (value = valuec)
						{
							if ((abs(x - cx) + abs(y - cy)) / 2.0 > (abs(x - i) + abs(y - j)) / 2.0)
							{
								cx = i;
								cy = j;
							}
						}
					}
				}
			}
		}
	}

	//si aucune direction n'a été prise

	if (cx < 0)
	{
		do
		{
			cx = ((int)x + rand() % 3 - 2);
			cy = ((int)y + rand() % 3 - 2);
		} while (cx == 0 && cy == 0);
	}

	float delta_dest_x = cx - x;
	float delta_dest_y = cy - y;

	float hypo = hypotf(delta_dest_x, delta_dest_y);
	float ndx = delta_dest_x / hypo, ndy = delta_dest_y / hypo;

	rotation = acos(ndx) * 180 / PI;

	if(ndy<0)
		rotation = 360 - rotation;

	rotation += 90;
	
	dx = ndx;
	dy = ndy;
};

void IA::change_dest()
{
	if (destination != home)
	{

	}
};