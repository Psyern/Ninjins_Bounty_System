#ifdef LBmaster_Groups
modded class LBGroupUI
{
	private ref obfc_BountyMapDrawer obfv_m_BountyMapDrawer;
	private CanvasWidget obfv_m_BountyDrawCanvas;
	private MapWidget obfv_m_BountyMapWidget;
	private float obfv_m_LastBountyUpdateTime = 0;
	private float obfv_m_LastBountyRequestTime = 0;
	override void OnShow()
	{
		super.OnShow();
		obfm_InitializeBountyMapDrawer();
		obfm_RequestBountiedPlayersFromServer();
	}
	private void obfm_InitializeBountyMapDrawer()
	{
		MapWidget currentMap = MapWidget.Cast(layoutRoot.FindAnyWidget("Map"));
		if (!currentMap)
			return;
		CanvasWidget oldCanvas = CanvasWidget.Cast(currentMap.FindAnyWidget("bountydrawCanvas"));
		if (oldCanvas)
		{
			oldCanvas.Unlink();
			oldCanvas = null;
		}
		if (!obfv_m_BountyMapDrawer || obfv_m_BountyMapDrawer.obfm_GetMapWidget() != currentMap)
		{
			obfc_BountyMapDrawer.obfm_ResetInstance(obfv_m_BountyMapWidget);
			obfv_m_BountyMapWidget = currentMap;
			Widget canvasLayout = g_Game.GetWorkspace().CreateWidgets("Ninjins_Bounty_System/gui/layouts/BountyMapCanvasOnly.layout", obfv_m_BountyMapWidget);
			if (!canvasLayout)
				return;
			obfv_m_BountyDrawCanvas = CanvasWidget.Cast(canvasLayout.FindAnyWidget("bountydrawCanvas"));
			if (!obfv_m_BountyDrawCanvas)
				return;
			obfv_m_BountyMapDrawer = obfc_BountyMapDrawer.GetInstance(obfv_m_BountyMapWidget, obfv_m_BountyDrawCanvas);
		}
	}
	private void obfm_RequestBountiedPlayersFromServer()
	{
		float currentTime = g_Game.GetTickTime();
		float requestCooldown = 2.0; 
		if (obfv_g_BountyConfig && obfv_g_BountyConfig.Map && obfv_g_BountyConfig.Map.BountyMapRequestCooldownSeconds > 0.0)
		{
			requestCooldown = obfv_g_BountyConfig.Map.BountyMapRequestCooldownSeconds;
		}
		float timeSinceLastRequest = currentTime - obfv_m_LastBountyRequestTime;
		if (timeSinceLastRequest > requestCooldown)
		{
			GetRPCManager().SendRPC("Ninjins_Bounty_System", "RequestBountiedPlayers", NULL, true, null);
			obfv_m_LastBountyRequestTime = currentTime;
		}
		if (!obfv_m_BountyMapDrawer)
			return;
		obfv_m_BountyMapDrawer.obfm_UpdateBountiedPlayers();
	}
	override void Update(float timeslice)
	{
		super.Update(timeslice);
		if (obfv_m_BountyMapDrawer && obfv_m_BountyMapDrawer.obfm_HasValidWidget())
		{
			float currentTime = g_Game.GetTickTime();
			float updateInterval = 1.0; 
			if (obfv_g_BountyConfig && obfv_g_BountyConfig.Map && obfv_g_BountyConfig.Map.BountyMapUpdateIntervalSeconds > 0.0)
			{
				updateInterval = obfv_g_BountyConfig.Map.BountyMapUpdateIntervalSeconds;
			}
			if (currentTime - obfv_m_LastBountyUpdateTime >= updateInterval)
			{
				obfv_m_BountyMapDrawer.obfm_UpdateBountiedPlayers();
				obfv_m_LastBountyUpdateTime = currentTime;
			}
			obfv_m_BountyMapDrawer.obfm_TriggerUpdate();
		}
	}
	override void OnHide()
	{
		super.OnHide();
		obfc_BountyMapDrawer.obfm_ResetInstance(obfv_m_BountyMapWidget);
		obfv_m_BountyMapDrawer = null;
		obfv_m_BountyDrawCanvas = null;
	}
}
#endif