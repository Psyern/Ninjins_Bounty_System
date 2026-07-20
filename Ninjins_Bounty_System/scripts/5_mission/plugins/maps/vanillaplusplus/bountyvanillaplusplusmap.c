#ifdef VanillaPPMap
modded class VPPMapMenu
{
	private ref BountyMapDrawer m_BountyMapDrawer;
	private CanvasWidget m_BountyDrawCanvas;
	private MapWidget m_BountyMapWidget;
	private float m_LastBountyUpdateTime = 0;
	private float m_LastBountyRequestTime = 0;
	override Widget Init()
	{
		super.Init();
		m_BountyMapWidget = MapWidget.Cast(layoutRoot.FindAnyWidget("Map_Widget"));
		if (!m_BountyMapWidget)
		{
			GetNinjins_Bounty_SystemLogger().LogWarning("[BountyVanillaPlusPlusMap] ERROR: MapWidget not found.");
			return layoutRoot;
		}
		CanvasWidget oldCanvas = CanvasWidget.Cast(m_BountyMapWidget.FindAnyWidget("bountydrawCanvas"));
		if (oldCanvas)
		{
			oldCanvas.Unlink();
			oldCanvas = null;
		}
		BountyMapDrawer.ResetInstance(m_BountyMapWidget);
		Widget canvasLayout = g_Game.GetWorkspace().CreateWidgets("Ninjins_Bounty_System/gui/layouts/BountyMapCanvasOnly.layout", m_BountyMapWidget);
		if (!canvasLayout)
		{
			GetNinjins_Bounty_SystemLogger().LogWarning("[BountyVanillaPlusPlusMap] ERROR: Failed to load canvas layout.");
			return layoutRoot;
		}
		m_BountyDrawCanvas = CanvasWidget.Cast(canvasLayout.FindAnyWidget("bountydrawCanvas"));
		if (!m_BountyDrawCanvas)
		{
			GetNinjins_Bounty_SystemLogger().LogWarning("[BountyVanillaPlusPlusMap] ERROR: drawCanvas not found in layout.");
			return layoutRoot;
		}
		m_BountyMapDrawer = BountyMapDrawer.GetInstance(m_BountyMapWidget, m_BountyDrawCanvas);
		if (!m_BountyMapDrawer)
		{
			GetNinjins_Bounty_SystemLogger().LogWarning("[BountyVanillaPlusPlusMap] ERROR: Failed to initialize BountyMapDrawer.");
		}
		return layoutRoot;
	}
	override void OnShow()
	{
		super.OnShow();
		float currentTime = g_Game.GetTickTime();
		float requestCooldown = 2.0; 
		if (g_BountyConfig && g_BountyConfig.Map && g_BountyConfig.Map.BountyMapRequestCooldownSeconds > 0.0)
		{
			requestCooldown = g_BountyConfig.Map.BountyMapRequestCooldownSeconds;
		}
		float timeSinceLastRequest = currentTime - m_LastBountyRequestTime;
		if (timeSinceLastRequest > requestCooldown)
		{
			GetRPCManager().SendRPC("Ninjins_Bounty_System", "RequestBountiedPlayers", NULL, true, null);
			m_LastBountyRequestTime = currentTime;
		}
		if (m_BountyMapDrawer)
		{
			m_BountyMapDrawer.UpdateBountiedPlayers();
		}
	}
	override void Update(float timeslice)
	{
		super.Update(timeslice);
		if (m_BountyMapDrawer && m_BountyMapDrawer.HasValidWidget())
		{
			float currentTime = g_Game.GetTickTime();
			float updateInterval = 1.0; 
			if (g_BountyConfig && g_BountyConfig.Map && g_BountyConfig.Map.BountyMapUpdateIntervalSeconds > 0.0)
			{
				updateInterval = g_BountyConfig.Map.BountyMapUpdateIntervalSeconds;
			}
			if (currentTime - m_LastBountyUpdateTime >= updateInterval)
			{
				m_BountyMapDrawer.UpdateBountiedPlayers();
				m_LastBountyUpdateTime = currentTime;
			}
			m_BountyMapDrawer.TriggerUpdate();
		}
	}
	override void OnHide()
	{
		super.OnHide();
		BountyMapDrawer.ResetInstance(m_BountyMapWidget);
		m_BountyMapDrawer = null;
		m_BountyDrawCanvas = null;
	}
}
#endif