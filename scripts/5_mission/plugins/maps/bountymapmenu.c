modded class MapMenu
{
    private ref BountyMapDrawer m_BountyMapDrawer;
    private CanvasWidget m_DrawCanvas;
    private MapWidget m_MapWidget;
    private float m_LastBountyUpdateTime = 0;
    private float m_LastBountyRequestTime = 0;
    override Widget Init()
    {
        super.Init();
        m_MapWidget = MapWidget.Cast(layoutRoot.FindAnyWidget("Map"));
        if (!m_MapWidget)
        {
            GetNinjins_Bounty_SystemLogger().LogWarning("[BountyMapMenu] ERROR: MapWidget not found.");
            return layoutRoot;
        }
        CanvasWidget oldCanvas = CanvasWidget.Cast(m_MapWidget.FindAnyWidget("bountydrawCanvas"));
        if (oldCanvas)
        {
            oldCanvas.Unlink();
            oldCanvas = null;
        }
        BountyMapDrawer.ResetInstance(m_MapWidget);
        Widget canvasLayout = g_Game.GetWorkspace().CreateWidgets("Ninjins_Bounty_System/gui/layouts/BountyMapCanvasOnly.layout", m_MapWidget);
        if (!canvasLayout)
        {
            GetNinjins_Bounty_SystemLogger().LogWarning("[BountyMapMenu] ERROR: Failed to load canvas layout.");
            return layoutRoot;
        }
        m_DrawCanvas = CanvasWidget.Cast(canvasLayout.FindAnyWidget("bountydrawCanvas"));
        if (!m_DrawCanvas)
        {
            GetNinjins_Bounty_SystemLogger().LogWarning("[BountyMapMenu] ERROR: drawCanvas not found in layout.");
            return layoutRoot;
        }
        m_BountyMapDrawer = BountyMapDrawer.GetInstance(m_MapWidget, m_DrawCanvas);
        if (!m_BountyMapDrawer)
        {
            GetNinjins_Bounty_SystemLogger().LogWarning("[BountyMapMenu] ERROR: Failed to initialize BountyMapDrawer.");
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
        BountyMapDrawer.ResetInstance(m_MapWidget);
        m_BountyMapDrawer = null;
        m_DrawCanvas = null;
    }
}