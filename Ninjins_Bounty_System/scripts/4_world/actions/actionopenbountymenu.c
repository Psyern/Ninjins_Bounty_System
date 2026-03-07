class ActionOpenBountyMenu : ActionInteractBase {
	override void CreateConditionComponents() 
	{
		m_ConditionItem = new CCINone;
		m_ConditionTarget = new CCTCursor;
	}
	override string GetText() {
		return "#open";
	}
	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item) 
	{
		if (!target || !target.GetObject())
			return false;
		Ninjins_Bounty_Board_Static tgt_entity = Ninjins_Bounty_Board_Static.Cast(target.GetObject());
		if (!tgt_entity)
			return false;
		if (IsMissionClient() && g_Game.GetUIManager() && g_Game.GetUIManager().GetMenu())
			return false;
		return true;
	}
	override void OnExecuteClient(ActionData action_data) 
	{
		PlayerBase player = PlayerBase.Cast(action_data.m_Player);
		if (!player || !player.GetIdentity())
			return;
		g_Game.GetCallQueue(CALL_CATEGORY_SYSTEM).CallLaterByName(g_Game.GetMission(), "OpenBountyBoardMenuDirect", 0, false);
	}
}