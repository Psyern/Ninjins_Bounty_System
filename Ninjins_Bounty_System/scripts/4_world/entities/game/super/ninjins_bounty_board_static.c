class Ninjins_Bounty_Board_Static: BuildingSuper
{
	void Ninjins_Bounty_Board_Static()
	{
		if (IsMissionHost())
			SetAllowDamage(false);
	}
}
// optional board models, same behaviour as the default board (selected via BoardClassName)
class Ninjins_Bounty_Board_Blackboard1: Ninjins_Bounty_Board_Static
{
}
class Ninjins_Bounty_Board_Blackboard2: Ninjins_Bounty_Board_Static
{
}
class Ninjins_Bounty_Board_Cactus: Ninjins_Bounty_Board_Static
{
}
class Ninjins_Bounty_Board_Outlaw: Ninjins_Bounty_Board_Static
{
}