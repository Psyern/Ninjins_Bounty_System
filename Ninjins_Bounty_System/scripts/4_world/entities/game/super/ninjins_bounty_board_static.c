class Ninjins_Bounty_Board_Static: BuildingSuper
{
	void Ninjins_Bounty_Board_Static()
	{
		if (IsMissionHost())
			SetAllowDamage(false);
	}
}