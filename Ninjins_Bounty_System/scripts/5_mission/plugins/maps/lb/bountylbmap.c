#ifdef LBmaster_Groups
modded class LBGroupUI
{
    private ref BountyMapDrawer m_BountyMapDrawer;
    private CanvasWidget m_DrawCanvas;
    private MapWidget m_BountyMapWidget;
    private float m_LastBountyUpdateTime = 0;
    private float m_LastBountyRequestTime = 0;
    override void OnShow()
    {
        super.OnShow();
        InitializeBountyMapDrawer();
        RequestBountiedPlayersFromServer();
    }
    private void InitializeBountyMapDrawer()
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
        if (!m_BountyMapDrawer || m_BountyMapDrawer.GetMapWidget() != currentMap)
        {
            BountyMapDrawer.ResetInstance(m_BountyMapWidget);
            m_BountyMapWidget = currentMap;
            Widget canvasLayout = g_Game.GetWorkspace().CreateWidgets("Ninjins_Bounty_System/gui/layouts/BountyMapCanvasOnly.layout", m_BountyMapWidget);
            if (!canvasLayout)
                return;
            m_DrawCanvas = CanvasWidget.Cast(canvasLayout.FindAnyWidget("bountydrawCanvas"));
            if (!m_DrawCanvas)
                return;
            m_BountyMapDrawer = BountyMapDrawer.GetInstance(m_BountyMapWidget, m_DrawCanvas);
        }
    }
    private void RequestBountiedPlayersFromServer()
    {
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
        if (!m_BountyMapDrawer)
            return;
        m_BountyMapDrawer.UpdateBountiedPlayers();
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
        m_DrawCanvas = null;
    }
}
#endif