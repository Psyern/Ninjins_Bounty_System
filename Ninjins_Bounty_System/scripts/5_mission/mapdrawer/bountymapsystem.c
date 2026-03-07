class BountyUtils
{
    static int screenWidth, screenHeight;
    static float widthScale, heightScale;
    static void UpdateScreenSize()
    {
        GetScreenSize(screenWidth, screenHeight);
        widthScale = screenWidth / 1920.0;
        heightScale = screenHeight / 1080.0;
    }
}
class BountyMapWrapper
{
    protected vector position;
    protected vector lastPosition;
    protected int lastColor;
    protected bool changed = false;
    protected CanvasWidget drawCanvas;
    void SetDrawCanvas(CanvasWidget canvas)
    {
        drawCanvas = canvas;
    }
    bool SetPosition(vector pos)
    {
        if (vector.DistanceSq(lastPosition, pos) > 0.01)
        {
            position = pos;
            lastPosition = pos;
            changed = true;
            return true;
        }
        return false;
    }
    bool SetColor(int color)
    {
        if (lastColor != color)
        {
            lastColor = color;
            changed = true;
            return true;
        }
        return false;
    }
    void Update(float mapScale, vector mapPos, MapWidget mapWidget, float xOffset, float yOffset)
    {
    }
    vector GetPosition()
    {
        return position;
    }
    int GetColor()
    {
        return lastColor;
    }
}
class BountyCircle : BountyMapWrapper
{
    const float EPS = 0.01;
    int circleWidth = 2;
    int m_Priority = 1;
    bool m_HideWhenNested = false;
    float radius = 100.0;
    ref array<ref BountyCircle> circleCheckList = new array<ref BountyCircle>();
    ref array<ref Param2<float, float>> intersecangles = new array<ref Param2<float, float>>();
    bool needUpdate = true;
    bool isCircleNested = false;
    float lastcircumf = -1;
    ref array<ref Param4<bool, bool, float, bool>> drawStepsPrepared = new array<ref Param4<bool, bool, float, bool>>();
    void Init(vector center, float radius_, int color, int prio)
    {
        this.position = center;
        this.radius = radius_;
        this.lastColor = color;
        this.m_Priority = prio;
        BountyUtils.UpdateScreenSize();
        if (g_BountyConfig && g_BountyConfig.Map && g_BountyConfig.Map.BountyCircleDrawingWidth > 0)
        {
            circleWidth = g_BountyConfig.Map.BountyCircleDrawingWidth;
        }
        else
        {
            circleWidth = 2;
        }
    }
    void SetHideWhenNested(bool hide)
    {
        m_HideWhenNested = hide;
    }
    override void Update(float mapScale, vector mapPos, MapWidget mapWidget, float xOffset, float yOffset)
    {
        if (m_HideWhenNested)
            return;
        if (!drawCanvas)
            return;
        vector screenPos = mapWidget.MapToScreen(position) + Vector(-xOffset, -yOffset, 0);
        float height = BountyUtils.screenHeight * 1.33333333;
        if (height > BountyUtils.screenWidth)
            height = BountyUtils.screenWidth;
        float screenScale = height / g_Game.GetWorld().GetWorldSize();
        float mapToScreen = mapScale / screenScale;
        float radiusScreen = radius / mapToScreen;
        if (radiusScreen <= 0)
            return;
        float radiusRoot = Math.Sqrt(radius);
        float circumf = 2.0 * Math.PI * radiusRoot;
        float part = 1.0 / radiusRoot;
        if (needUpdate)
            CalcEveryCircleIntersection();
        if (needUpdate || lastcircumf != circumf)
        {
            MathForCircleIntersections(circumf, part);
            lastcircumf = circumf;
        }
        needUpdate = false;
        float angle2 = 0.0;
        float rawX2 = radius;
        float rawY2 = 0.0;
        float newX2 = screenPos[0] + radius / mapToScreen;
        float newY2 = screenPos[1];
        int i = 0;
        Param4<bool, bool, float, bool> param;
        for (i = 0; i < drawStepsPrepared.Count(); i++)
        {
            param = drawStepsPrepared.Get(i);
            int stepIndex = i + 1; 
            float angle1 = angle2;
            angle2 = part * stepIndex;
            float rawX1 = rawX2;
            rawX2 = radius * Math.Cos(angle2);
            float rawY1 = rawY2;
            rawY2 = -radius * Math.Sin(angle2);
            float newX1 = newX2;
            newX2 = screenPos[0] + rawX2 / mapToScreen;
            float newY1 = newY2;
            newY2 = screenPos[1] + rawY2 / mapToScreen;
            if (param.param1)
                continue;
            if (param.param2)
            {
                float offset = 0.0015;
                float edgeAngle = param.param3;
                if (param.param4)
                    edgeAngle += offset;
                else
                    edgeAngle -= offset;
                float newX3 = screenPos[0] + radius * Math.Cos(edgeAngle) / mapToScreen;
                float newY3 = screenPos[1] - radius * Math.Sin(edgeAngle) / mapToScreen;
                if (param.param4)
                    drawCanvas.DrawLine(newX3, newY3, newX2, newY2, circleWidth, lastColor);
                else
                    drawCanvas.DrawLine(newX3, newY3, newX1, newY1, circleWidth, lastColor);
                continue;
            }
            drawCanvas.DrawLine(newX1, newY1, newX2, newY2, circleWidth, lastColor);
        }
    }
    void CalcEveryCircleIntersection()
    {
        intersecangles.Clear();
        if (!circleCheckList)
            return;
        int i;
        BountyCircle circ;
        for (i = 0; i < circleCheckList.Count(); i++)
        {
            circ = circleCheckList.Get(i);
            if (circ == this)
                continue;
            if (circ.m_Priority < m_Priority)
                continue;
            float dx = circ.position[0] - position[0];
            float dz = circ.position[2] - position[2];
            float d = Math.Sqrt(dx * dx + dz * dz);
            if (d >= radius + circ.radius || d <= 0)
                continue;
            float a = (radius * radius - circ.radius * circ.radius + d * d) / (2.0 * d);
            float h = Math.Sqrt(radius * radius - a * a);
            float hd = h / d;
            float px = position[0] + dx * a / d;
            float pz = position[2] + dz * a / d;
            float x1 = (px + hd * (circ.position[2] - position[2])) - position[0];
            float z1 = (pz - hd * (circ.position[0] - position[0])) - position[2];
            float x2 = (px - hd * (circ.position[2] - position[2])) - position[0];
            float z2 = (pz + hd * (circ.position[0] - position[0])) - position[2];
            float dist1 = Math.Sqrt(x1 * x1 + z1 * z1);
            float dist2 = Math.Sqrt(x2 * x2 + z2 * z2);
            if (dist1 <= 0 || dist2 <= 0)
                continue;
            float ang1 = Math.Acos(x1 / dist1);
            if (z1 < 0) ang1 = Math.PI2 - ang1;
            float ang2 = Math.Acos(x2 / dist2);
            if (z2 < 0) ang2 = Math.PI2 - ang2;
            if (ang1 < ang2)
                intersecangles.Insert(new Param2<float, float>(ang1, ang2));
            else
            {
                intersecangles.Insert(new Param2<float, float>(-1, ang2));
                intersecangles.Insert(new Param2<float, float>(ang1, Math.PI2 + 1));
            }
        }
    }
    void CalculateInsideCircle()
    {
        isCircleNested = false;
        int i;
        BountyCircle circ;
        for (i = 0; i < circleCheckList.Count(); i++)
        {
            circ = circleCheckList.Get(i);
            if (circ == this)
                continue;
            if (!m_HideWhenNested && (circ.m_Priority < m_Priority))
                continue;
            float dx = circ.position[0] - position[0];
            float dz = circ.position[2] - position[2];
            float d = Math.Sqrt(dx * dx + dz * dz);
            if (d + radius <= circ.radius + EPS)
            {
                isCircleNested = true;
            }
        }
    }
    void MathForCircleIntersections(float circumf, float part)
    {
        drawStepsPrepared.Clear();
        float ang2 = 0.0;
        int i;
        for (i = 1; i <= circumf + 1; i++)
        {
            float ang1 = ang2;
            ang2 = part * i;
            bool intersecting = false;
            bool edge = false;
            float edgeAngle = 0.0;
            bool clipDirectionForward = false;
            Param2<float, float> span;
            int j;
            for (j = 0; j < intersecangles.Count(); j++)
            {
                span = intersecangles.Get(j);
                if (ang2 > span.param1 && ang1 < span.param2)
                {
                    if (span.param1 < ang1)
                    {
                        edgeAngle = span.param2;
                        clipDirectionForward = true;
                    }
                    else
                    {
                        edgeAngle = span.param1;
                        clipDirectionForward = false;
                    }
                    edge = true;
                }
                if (ang1 > span.param1 && ang2 < span.param2)
                {
                    intersecting = true;
                    break;
                }
            }
            drawStepsPrepared.Insert(
                new Param4<bool, bool, float, bool>(intersecting, edge, edgeAngle, clipDirectionForward));
        }
    }
    void CirclesOthers(array<ref BountyCircle> circles)
    {
        circleCheckList.Clear();
        int i;
        BountyCircle circ;
        for (i = 0; i < circles.Count(); i++)
        {
            circ = circles.Get(i);
            circleCheckList.Insert(circ);
        }
        needUpdate = true;
        CalculateInsideCircle();
    }
}
class BountyMapManager
{
    private MapWidget mapWidget;
    private CanvasWidget drawCanvas;
    private ref array<ref BountyMapWrapper> markers = new array<ref BountyMapWrapper>();
    private ref array<ref BountyCircle> circles = new array<ref BountyCircle>();
    private float lastMapScale;
    private vector lastMapPos;
    private float xOffset, yOffset;
    void BountyMapManager(MapWidget mapW, CanvasWidget canvas)
    {
        mapWidget = mapW;
        drawCanvas = canvas;
        mapWidget.GetScreenPos(xOffset, yOffset);
    }
    void UpdateOffsets()
    {
        mapWidget.GetScreenPos(xOffset, yOffset);
    }
    BountyCircle AddCircle(vector pos, float radius, int color, bool hideWhenNested = false, int priority = 1)
    {
        BountyCircle circle = new BountyCircle();
        circle.SetDrawCanvas(drawCanvas);
        circle.Init(pos, radius, color, priority);
        circle.SetHideWhenNested(hideWhenNested);
        markers.Insert(circle);
        circles.Insert(circle);
        return circle;
    }
    void Update()
    {
        if (!mapWidget || !drawCanvas)
            return;
        float scale = mapWidget.GetScale();
        vector pos = mapWidget.GetMapPos();
        UpdateOffsets();
        drawCanvas.Clear();
        int i;
        BountyCircle c;
        for (i = 0; i < circles.Count(); i++)
        {
            c = circles.Get(i);
            c.CirclesOthers(circles);
        }
        BountyMapWrapper marker;
        for (i = 0; i < markers.Count(); i++)
        {
            marker = markers.Get(i);
            marker.Update(scale, pos, mapWidget, xOffset, yOffset);
        }
        lastMapScale = scale;
        lastMapPos = pos;
    }
    void ClearMarkers()
    {
        if (drawCanvas)
        {
            drawCanvas.Clear();
        }
        markers.Clear();
        circles.Clear();
    }
    bool HasMarkers()
    {
        return markers && markers.Count() > 0;
    }
}
class BountyMapDrawer
{
    private MapWidget m_MapWidget;
    private CanvasWidget m_DrawCanvas;
    private ref BountyMapManager m_MarkerManager;
    private static ref map<int, ref BountyMapDrawer> s_Instances = new map<int, ref BountyMapDrawer>();
    void BountyMapDrawer(MapWidget mapWidget, CanvasWidget canvas)
    {
        BountyUtils.UpdateScreenSize();
        m_MapWidget = mapWidget;
        m_DrawCanvas = canvas;
        if (!m_MapWidget || !m_DrawCanvas)
        {
            GetNinjins_Bounty_SystemLogger().LogWarning("[BountyMapDrawer] ERROR: mapWidget or drawCanvas is NULL!");
            return;
        }
        m_MarkerManager = new BountyMapManager(m_MapWidget, m_DrawCanvas);
    }
    static BountyMapDrawer GetInstance(MapWidget mapWidget, CanvasWidget canvas)
    {
        if (!mapWidget || !canvas)
            return null;
        int key = mapWidget.ToString().Hash();
        if (!s_Instances.Contains(key))
        {
            s_Instances.Set(key, new BountyMapDrawer(mapWidget, canvas));
        }
        return s_Instances.Get(key);
    }
    static void ResetInstance(MapWidget mapWidget = null)
    {
        if (mapWidget)
        {
            int key = mapWidget.ToString().Hash();
            if (s_Instances.Contains(key))
            {
                s_Instances.Get(key).ClearMap();
                s_Instances.Remove(key);
            }
        }
        else
        {
            int id;
            BountyMapDrawer drawer;
            array<int> keys = s_Instances.GetKeyArray();
            int i;
            for (i = 0; i < keys.Count(); i++)
            {
                id = keys.Get(i);
                drawer = s_Instances.Get(id);
                if (drawer)
                {
                    drawer.ClearMap();
                }
            }
            s_Instances.Clear();
        }
    }
    MapWidget GetMapWidget()
    {
        return m_MapWidget;
    }
    bool HasValidWidget()
    {
        return m_MapWidget && m_MapWidget.IsVisible();
    }
    CanvasWidget GetDrawCanvas()
    {
        return m_DrawCanvas;
    }
    void Update()
    {
        if (m_MarkerManager)
        {
            m_MarkerManager.Update();
        }
    }
    void UpdateBountiedPlayers()
    {
        if (!m_DrawCanvas || !m_MarkerManager || !m_MapWidget)
        {
            GetNinjins_Bounty_SystemLogger().LogWarning("[BountyMapDrawer] UpdateBountiedPlayers: Missing canvas, manager, or map widget");
            return;
        }
        bool enableDrawing = true; 
        m_MarkerManager.ClearMarkers();
        m_DrawCanvas.Clear();
        array<ref BountyPlayerData> bountiedPlayers = BountyMapBridge.GetBountiedPlayers();
        if (!bountiedPlayers || bountiedPlayers.Count() == 0)
        {
            return;
        }
        GetNinjins_Bounty_SystemLogger().LogInfo("[BountyMapDrawer] Updating " + bountiedPlayers.Count().ToString() + " bountied players");
        bool hideWhenNested = false;
        int priority = 1;
        int i;
        BountyPlayerData playerData;
        for (i = 0; i < bountiedPlayers.Count(); i++)
        {
            playerData = bountiedPlayers.Get(i);
            if (!playerData)
            {
                GetNinjins_Bounty_SystemLogger().LogWarning("[BountyMapDrawer] Player data is null at index " + i.ToString());
                continue;
            }
            if (playerData.Position[0] == 0 && playerData.Position[1] == 0 && playerData.Position[2] == 0)
            {
                GetNinjins_Bounty_SystemLogger().LogWarning("[BountyMapDrawer] Player " + playerData.PlayerName + " has invalid position");
                continue;
            }
            float circleRadius = 100.0;
            if (playerData.CircleRadius > 0.0)
            {
                circleRadius = playerData.CircleRadius;
            }
            int circleColor = ARGB(255, 255, 0, 0);
            if (playerData.CircleColor != 0)
            {
                circleColor = playerData.CircleColor;
            }
            GetNinjins_Bounty_SystemLogger().LogInfo("[BountyMapDrawer] Drawing circle for " + playerData.PlayerName + " at " + playerData.Position.ToString() + " with radius " + circleRadius.ToString());
            float currentRadius = circleRadius;
            float maxTime = playerData.BountyDurationSeconds;
            if (maxTime > 0.0 && playerData.TimeRemaining > 0.0)
            {
                float timeRatio = playerData.TimeRemaining / maxTime;
                float minRadius = playerData.CircleMinRadius;
                if (minRadius <= 0.0)
                {
                    minRadius = circleRadius * 0.1; 
                }
                if (playerData.ReduceRadiusOverTime)
                {
                    currentRadius = minRadius + (circleRadius - minRadius) * timeRatio;
                }
                else if (playerData.IncreaseRadiusOverTime)
                {
                    float invertedRatio = 1.0 - timeRatio;
                    currentRadius = minRadius + (circleRadius - minRadius) * invertedRatio;
                }
            }
            vector circleCenter = CalculateCircleCenterWithOffset(playerData.Position, currentRadius, playerData.CachedOffsetMultiplier, playerData.CachedOffsetAngle);
            m_MarkerManager.AddCircle(circleCenter, currentRadius, circleColor, hideWhenNested, priority);
        }
        m_MarkerManager.Update();
    }
    void TriggerUpdate()
    {
        if (!m_MapWidget || !m_MarkerManager)
            return;
        m_MarkerManager.UpdateOffsets();
        m_MarkerManager.Update();
    }
    void UpdateOffsets()
    {
        if (m_MarkerManager)
            m_MarkerManager.UpdateOffsets();
    }
    void ClearMap()
    {
        if (m_DrawCanvas)
        {
            m_DrawCanvas.Clear();
            m_DrawCanvas.Unlink();
            m_DrawCanvas = null;
        }
        if (m_MarkerManager)
            m_MarkerManager.ClearMarkers();
    }
    private vector CalculateCircleCenterWithOffset(vector playerPosition, float currentRadius, float cachedMultiplier, float cachedAngle)
    {
        vector circleCenter = playerPosition;
        if (cachedMultiplier > 0.0 && currentRadius > 0.0)
        {
            float offsetDistance = currentRadius * cachedMultiplier;
            float offsetX = Math.Sin(cachedAngle) * offsetDistance;
            float offsetZ = Math.Cos(cachedAngle) * offsetDistance;
            circleCenter[0] = playerPosition[0] + offsetX;
            circleCenter[2] = playerPosition[2] + offsetZ;
            circleCenter[1] = playerPosition[1];
        }
        return circleCenter;
    }
    void DrawBountyCircle(vector center, float radius, int color, bool hideWhenNested = false, int priority = 1)
    {
        if (!m_MarkerManager)
            return;
        m_MarkerManager.AddCircle(center, radius, color, hideWhenNested, priority);
    }
    void ClearAll()
    {
        if (m_MarkerManager)
        {
            m_MarkerManager.ClearMarkers();
        }
    }
    bool HasMarkers()
    {
        if (m_MarkerManager)
        {
            return m_MarkerManager.HasMarkers();
        }
        return false;
    }
}