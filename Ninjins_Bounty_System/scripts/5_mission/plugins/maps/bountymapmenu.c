modded class MapMenu
{
	private ref obfc_BountyMapDrawer obfv_m_BountyMapDrawer;
	private CanvasWidget obfv_m_BountyDrawCanvas;
	private MapWidget obfv_m_BountyMapWidget;
	private float obfv_m_LastBountyUpdateTime = 0;
	private float obfv_m_LastBountyRequestTime = 0;
	override Widget Init()
	{
		super.Init();
		obfv_m_BountyMapWidget = MapWidget.Cast(layoutRoot.FindAnyWidget("Map"));
		if (!obfv_m_BountyMapWidget)
		{
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogWarning("[BountyMapMenu] ERROR: MapWidget not found.");
			return layoutRoot;
		}
		CanvasWidget oldCanvas = CanvasWidget.Cast(obfv_m_BountyMapWidget.FindAnyWidget("bountydrawCanvas"));
		if (oldCanvas)
		{
			oldCanvas.Unlink();
			oldCanvas = null;
		}
		obfc_BountyMapDrawer.obfm_ResetInstance(obfv_m_BountyMapWidget);
		Widget canvasLayout = g_Game.GetWorkspace().CreateWidgets("Ninjins_Bounty_System/gui/layouts/BountyMapCanvasOnly.layout", obfv_m_BountyMapWidget);
		if (!canvasLayout)
		{
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogWarning("[BountyMapMenu] ERROR: Failed to load canvas layout.");
			return layoutRoot;
		}
		obfv_m_BountyDrawCanvas = CanvasWidget.Cast(canvasLayout.FindAnyWidget("bountydrawCanvas"));
		if (!obfv_m_BountyDrawCanvas)
		{
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogWarning("[BountyMapMenu] ERROR: drawCanvas not found in layout.");
			return layoutRoot;
		}
		obfv_m_BountyMapDrawer = obfc_BountyMapDrawer.GetInstance(obfv_m_BountyMapWidget, obfv_m_BountyDrawCanvas);
		if (!obfv_m_BountyMapDrawer)
		{
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogWarning("[BountyMapMenu] ERROR: Failed to initialize BountyMapDrawer.");
		}
		return layoutRoot;
	}
	override void OnShow()
	{
		super.OnShow();
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
		if (obfv_m_BountyMapDrawer)
		{
			obfv_m_BountyMapDrawer.obfm_UpdateBountiedPlayers();
		}
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