class obfc_BountyUtils
{
	static int obfv_screenWidth;
	static int obfv_screenHeight;
	static float obfv_widthScale;
	static float obfv_heightScale;
	static void obfm_UpdateScreenSize()
	{
		GetScreenSize(obfv_screenWidth, obfv_screenHeight);
		obfv_widthScale = obfv_screenWidth / 1920.0;
		obfv_heightScale = obfv_screenHeight / 1080.0;
	}
}
class obfc_BountyMapWrapper
{
	protected vector obfv_position;
	protected vector obfv_lastPosition;
	protected int obfv_lastColor;
	protected bool obfv_changed = false;
	protected CanvasWidget obfv_drawCanvas;
	void SetDrawCanvas(CanvasWidget canvas)
	{
		obfv_drawCanvas = canvas;
	}
	bool SetPosition(vector pos)
	{
		if (vector.DistanceSq(obfv_lastPosition, pos) > 0.01)
		{
			obfv_position = pos;
			obfv_lastPosition = pos;
			obfv_changed = true;
			return true;
		}
		return false;
	}
	bool SetColor(int color)
	{
		if (obfv_lastColor != color)
		{
			obfv_lastColor = color;
			obfv_changed = true;
			return true;
		}
		return false;
	}
	void Update(float mapScale, vector mapPos, MapWidget obfv_mapWidget, float obfv_xOffset, float obfv_yOffset)
	{
	}
	vector GetPosition()
	{
		return obfv_position;
	}
	int obfm_GetColor()
	{
		return obfv_lastColor;
	}
}
class obfc_BountyCircle : obfc_BountyMapWrapper
{
	const float obfv_EPS = 0.01;
	int obfv_circleWidth = 2;
	int obfv_m_Priority = 1;
	bool obfv_m_HideWhenNested = false;
	float obfv_radius = 100.0;
	ref array<ref obfc_BountyCircle> obfv_circleCheckList = new array<ref obfc_BountyCircle>();
	ref array<ref Param2<float, float>> obfv_intersecangles = new array<ref Param2<float, float>>();
	bool obfv_needUpdate = true;
	bool obfv_isCircleNested = false;
	float obfv_lastcircumf = -1;
	ref array<ref Param4<bool, bool, float, bool>> obfv_drawStepsPrepared = new array<ref Param4<bool, bool, float, bool>>();
	void Init(vector center, float radius_, int color, int prio)
	{
		this.obfv_position = center;
		this.obfv_radius = radius_;
		this.obfv_lastColor = color;
		this.obfv_m_Priority = prio;
		obfc_BountyUtils.obfm_UpdateScreenSize();
		if (obfv_g_BountyConfig && obfv_g_BountyConfig.Map && obfv_g_BountyConfig.Map.BountyCircleDrawingWidth > 0)
		{
			obfv_circleWidth = obfv_g_BountyConfig.Map.BountyCircleDrawingWidth;
		}
		else
		{
			obfv_circleWidth = 2;
		}
	}
	void obfm_SetHideWhenNested(bool hide)
	{
		obfv_m_HideWhenNested = hide;
	}
	override void Update(float mapScale, vector mapPos, MapWidget obfv_mapWidget, float obfv_xOffset, float obfv_yOffset)
	{
		if (obfv_m_HideWhenNested)
			return;
		if (!obfv_drawCanvas)
			return;
		vector screenPos = obfv_mapWidget.MapToScreen(obfv_position) + Vector(-obfv_xOffset, -obfv_yOffset, 0);
		float height = obfc_BountyUtils.obfv_screenHeight * 1.33333333;
		if (height > obfc_BountyUtils.obfv_screenWidth)
			height = obfc_BountyUtils.obfv_screenWidth;
		float screenScale = height / g_Game.GetWorld().GetWorldSize();
		float mapToScreen = mapScale / screenScale;
		float radiusScreen = obfv_radius / mapToScreen;
		if (radiusScreen <= 0)
			return;
		float radiusRoot = Math.Sqrt(obfv_radius);
		float circumf = 2.0 * Math.PI * radiusRoot;
		float part = 1.0 / radiusRoot;
		if (obfv_needUpdate)
			obfm_CalcEveryCircleIntersection();
		if (obfv_needUpdate || obfv_lastcircumf != circumf)
		{
			obfm_MathForCircleIntersections(circumf, part);
			obfv_lastcircumf = circumf;
		}
		obfv_needUpdate = false;
		float angle2 = 0.0;
		float rawX2 = obfv_radius;
		float rawY2 = 0.0;
		float newX2 = screenPos[0] + obfv_radius / mapToScreen;
		float newY2 = screenPos[1];
		int i = 0;
		Param4<bool, bool, float, bool> param;
		for (i = 0; i < obfv_drawStepsPrepared.Count(); i++)
		{
			param = obfv_drawStepsPrepared.Get(i);
			int stepIndex = i + 1; 
			float angle1 = angle2;
			angle2 = part * stepIndex;
			float rawX1 = rawX2;
			rawX2 = obfv_radius * Math.Cos(angle2);
			float rawY1 = rawY2;
			rawY2 = -obfv_radius * Math.Sin(angle2);
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
				float newX3 = screenPos[0] + obfv_radius * Math.Cos(edgeAngle) / mapToScreen;
				float newY3 = screenPos[1] - obfv_radius * Math.Sin(edgeAngle) / mapToScreen;
				if (param.param4)
					obfv_drawCanvas.DrawLine(newX3, newY3, newX2, newY2, obfv_circleWidth, obfv_lastColor);
				else
					obfv_drawCanvas.DrawLine(newX3, newY3, newX1, newY1, obfv_circleWidth, obfv_lastColor);
				continue;
			}
			obfv_drawCanvas.DrawLine(newX1, newY1, newX2, newY2, obfv_circleWidth, obfv_lastColor);
		}
	}
	void obfm_CalcEveryCircleIntersection()
	{
		obfv_intersecangles.Clear();
		if (!obfv_circleCheckList)
			return;
		int i;
		obfc_BountyCircle circ;
		for (i = 0; i < obfv_circleCheckList.Count(); i++)
		{
			circ = obfv_circleCheckList.Get(i);
			if (circ == this)
				continue;
			if (circ.obfv_m_Priority < obfv_m_Priority)
				continue;
			float dx = circ.obfv_position[0] - obfv_position[0];
			float dz = circ.obfv_position[2] - obfv_position[2];
			float d = Math.Sqrt(dx * dx + dz * dz);
			if (d >= obfv_radius + circ.obfv_radius || d <= 0)
				continue;
			float a = (obfv_radius * obfv_radius - circ.obfv_radius * circ.obfv_radius + d * d) / (2.0 * d);
			float h = Math.Sqrt(obfv_radius * obfv_radius - a * a);
			float hd = h / d;
			float px = obfv_position[0] + dx * a / d;
			float pz = obfv_position[2] + dz * a / d;
			float x1 = (px + hd * (circ.obfv_position[2] - obfv_position[2])) - obfv_position[0];
			float z1 = (pz - hd * (circ.obfv_position[0] - obfv_position[0])) - obfv_position[2];
			float x2 = (px - hd * (circ.obfv_position[2] - obfv_position[2])) - obfv_position[0];
			float z2 = (pz + hd * (circ.obfv_position[0] - obfv_position[0])) - obfv_position[2];
			float dist1 = Math.Sqrt(x1 * x1 + z1 * z1);
			float dist2 = Math.Sqrt(x2 * x2 + z2 * z2);
			if (dist1 <= 0 || dist2 <= 0)
				continue;
			float ang1 = Math.Acos(x1 / dist1);
			if (z1 < 0) ang1 = Math.PI2 - ang1;
			float ang2 = Math.Acos(x2 / dist2);
			if (z2 < 0) ang2 = Math.PI2 - ang2;
			if (ang1 < ang2)
				obfv_intersecangles.Insert(new Param2<float, float>(ang1, ang2));
			else
			{
				obfv_intersecangles.Insert(new Param2<float, float>(-1, ang2));
				obfv_intersecangles.Insert(new Param2<float, float>(ang1, Math.PI2 + 1));
			}
		}
	}
	void obfm_CalculateInsideCircle()
	{
		obfv_isCircleNested = false;
		int i;
		obfc_BountyCircle circ;
		for (i = 0; i < obfv_circleCheckList.Count(); i++)
		{
			circ = obfv_circleCheckList.Get(i);
			if (circ == this)
				continue;
			if (!obfv_m_HideWhenNested && (circ.obfv_m_Priority < obfv_m_Priority))
				continue;
			float dx = circ.obfv_position[0] - obfv_position[0];
			float dz = circ.obfv_position[2] - obfv_position[2];
			float d = Math.Sqrt(dx * dx + dz * dz);
			if (d + obfv_radius <= circ.obfv_radius + obfv_EPS)
			{
				obfv_isCircleNested = true;
			}
		}
	}
	void obfm_MathForCircleIntersections(float circumf, float part)
	{
		obfv_drawStepsPrepared.Clear();
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
			for (j = 0; j < obfv_intersecangles.Count(); j++)
			{
				span = obfv_intersecangles.Get(j);
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
			Param4<bool, bool, float, bool> drawStep = new Param4<bool, bool, float, bool>(intersecting, edge, edgeAngle, clipDirectionForward);
			obfv_drawStepsPrepared.Insert(drawStep);
		}
	}
	void obfm_CirclesOthers(array<ref obfc_BountyCircle> obfv_circles)
	{
		obfv_circleCheckList.Clear();
		int i;
		obfc_BountyCircle circ;
		for (i = 0; i < obfv_circles.Count(); i++)
		{
			circ = obfv_circles.Get(i);
			obfv_circleCheckList.Insert(circ);
		}
		obfv_needUpdate = true;
		obfm_CalculateInsideCircle();
	}
}
class obfc_BountyMapManager
{
	private MapWidget obfv_mapWidget;
	private CanvasWidget obfv_drawCanvas;
	private ref array<ref obfc_BountyMapWrapper> obfv_markers = new array<ref obfc_BountyMapWrapper>();
	private ref array<ref obfc_BountyCircle> obfv_circles = new array<ref obfc_BountyCircle>();
	private float obfv_lastMapScale;
	private vector obfv_lastMapPos;
	private float obfv_xOffset;
	private float obfv_yOffset;
	void obfc_BountyMapManager(MapWidget mapW, CanvasWidget canvas)
	{
		obfv_mapWidget = mapW;
		obfv_drawCanvas = canvas;
		obfv_mapWidget.GetScreenPos(obfv_xOffset, obfv_yOffset);
	}
	void obfm_UpdateOffsets()
	{
		obfv_mapWidget.GetScreenPos(obfv_xOffset, obfv_yOffset);
	}
	obfc_BountyCircle obfm_AddCircle(vector pos, float obfv_radius, int color, bool hideWhenNested = false, int priority = 1)
	{
		obfc_BountyCircle circle = new obfc_BountyCircle();
		circle.SetDrawCanvas(obfv_drawCanvas);
		circle.Init(pos, obfv_radius, color, priority);
		circle.obfm_SetHideWhenNested(hideWhenNested);
		obfv_markers.Insert(circle);
		obfv_circles.Insert(circle);
		return circle;
	}
	void Update()
	{
		if (!obfv_mapWidget || !obfv_drawCanvas)
			return;
		float scale = obfv_mapWidget.GetScale();
		vector pos = obfv_mapWidget.GetMapPos();
		obfm_UpdateOffsets();
		obfv_drawCanvas.Clear();
		int i;
		obfc_BountyCircle c;
		for (i = 0; i < obfv_circles.Count(); i++)
		{
			c = obfv_circles.Get(i);
			c.obfm_CirclesOthers(obfv_circles);
		}
		obfc_BountyMapWrapper marker;
		for (i = 0; i < obfv_markers.Count(); i++)
		{
			marker = obfv_markers.Get(i);
			marker.Update(scale, pos, obfv_mapWidget, obfv_xOffset, obfv_yOffset);
		}
		obfv_lastMapScale = scale;
		obfv_lastMapPos = pos;
	}
	void obfm_ClearMarkers()
	{
		if (obfv_drawCanvas)
		{
			obfv_drawCanvas.Clear();
		}
		obfv_markers.Clear();
		obfv_circles.Clear();
	}
	bool obfm_HasMarkers()
	{
		return obfv_markers && obfv_markers.Count() > 0;
	}
}
class obfc_BountyMapDrawer
{
	private MapWidget obfv_m_MapWidget;
	private CanvasWidget obfv_m_DrawCanvas;
	private ref obfc_BountyMapManager obfv_m_MarkerManager;
	private static ref map<int, ref obfc_BountyMapDrawer> obfv_s_Instances = new map<int, ref obfc_BountyMapDrawer>();
	void obfc_BountyMapDrawer(MapWidget obfv_mapWidget, CanvasWidget canvas)
	{
		obfc_BountyUtils.obfm_UpdateScreenSize();
		obfv_m_MapWidget = obfv_mapWidget;
		obfv_m_DrawCanvas = canvas;
		if (!obfv_m_MapWidget || !obfv_m_DrawCanvas)
		{
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogWarning("[BountyMapDrawer] ERROR: mapWidget or drawCanvas is NULL!");
			return;
		}
		obfv_m_MarkerManager = new obfc_BountyMapManager(obfv_m_MapWidget, obfv_m_DrawCanvas);
	}
	static obfc_BountyMapDrawer GetInstance(MapWidget obfv_mapWidget, CanvasWidget canvas)
	{
		if (!obfv_mapWidget || !canvas)
			return null;
		int key = obfv_mapWidget.ToString().Hash();
		if (!obfv_s_Instances.Contains(key))
		{
			obfv_s_Instances.Set(key, new obfc_BountyMapDrawer(obfv_mapWidget, canvas));
		}
		return obfv_s_Instances.Get(key);
	}
	static void obfm_ResetInstance(MapWidget obfv_mapWidget = null)
	{
		if (obfv_mapWidget)
		{
			int key = obfv_mapWidget.ToString().Hash();
			if (obfv_s_Instances.Contains(key))
			{
				obfv_s_Instances.Get(key).obfm_ClearMap();
				obfv_s_Instances.Remove(key);
			}
		}
		else
		{
			int id;
			obfc_BountyMapDrawer drawer;
			array<int> keys = obfv_s_Instances.GetKeyArray();
			int i;
			for (i = 0; i < keys.Count(); i++)
			{
				id = keys.Get(i);
				drawer = obfv_s_Instances.Get(id);
				if (drawer)
				{
					drawer.obfm_ClearMap();
				}
			}
			obfv_s_Instances.Clear();
		}
	}
	MapWidget obfm_GetMapWidget()
	{
		return obfv_m_MapWidget;
	}
	bool obfm_HasValidWidget()
	{
		return obfv_m_MapWidget && obfv_m_MapWidget.IsVisible();
	}
	CanvasWidget obfm_GetDrawCanvas()
	{
		return obfv_m_DrawCanvas;
	}
	void Update()
	{
		if (obfv_m_MarkerManager)
		{
			obfv_m_MarkerManager.Update();
		}
	}
	void obfm_UpdateBountiedPlayers()
	{
		if (!obfv_m_DrawCanvas || !obfv_m_MarkerManager || !obfv_m_MapWidget)
		{
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogWarning("[BountyMapDrawer] UpdateBountiedPlayers: Missing canvas, manager, or map widget");
			return;
		}
		bool enableDrawing = true; 
		obfv_m_MarkerManager.obfm_ClearMarkers();
		obfv_m_DrawCanvas.Clear();
		array<ref obfc_BountyPlayerData> bountiedPlayers = obfc_BountyMapBridge.obfm_GetBountiedPlayers();
		if (!bountiedPlayers || bountiedPlayers.Count() == 0)
		{
			return;
		}
		obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[BountyMapDrawer] Updating " + bountiedPlayers.Count().ToString() + " bountied players");
		bool hideWhenNested = false;
		int priority = 1;
		int i;
		obfc_BountyPlayerData playerData;
		for (i = 0; i < bountiedPlayers.Count(); i++)
		{
			playerData = bountiedPlayers.Get(i);
			if (!playerData)
			{
				obfm_GetNinjins_Bounty_SystemLogger().obfm_LogWarning("[BountyMapDrawer] Player data is null at index " + i.ToString());
				continue;
			}
			if (playerData.Position[0] == 0 && playerData.Position[1] == 0 && playerData.Position[2] == 0)
			{
				obfm_GetNinjins_Bounty_SystemLogger().obfm_LogWarning("[BountyMapDrawer] Player " + playerData.obfv_PlayerName + " has invalid position");
				continue;
			}
			float circleRadius = 100.0;
			if (playerData.obfv_CircleRadius > 0.0)
			{
				circleRadius = playerData.obfv_CircleRadius;
			}
			int circleColor = ARGB(255, 255, 0, 0);
			if (playerData.obfv_CircleColor != 0)
			{
				circleColor = playerData.obfv_CircleColor;
			}
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[BountyMapDrawer] Drawing circle for " + playerData.obfv_PlayerName + " at " + playerData.Position.ToString() + " with radius " + circleRadius.ToString());
			float currentRadius = circleRadius;
			float maxTime = playerData.BountyDurationSeconds;
			if (maxTime > 0.0 && playerData.obfv_TimeRemaining > 0.0)
			{
				float timeRatio = playerData.obfv_TimeRemaining / maxTime;
				float minRadius = playerData.obfv_CircleMinRadius;
				if (minRadius <= 0.0)
				{
					minRadius = circleRadius * 0.1; 
				}
				if (playerData.obfv_ReduceRadiusOverTime)
				{
					currentRadius = minRadius + (circleRadius - minRadius) * timeRatio;
				}
				else if (playerData.obfv_IncreaseRadiusOverTime)
				{
					float invertedRatio = 1.0 - timeRatio;
					currentRadius = minRadius + (circleRadius - minRadius) * invertedRatio;
				}
			}
			vector circleCenter = obfm_CalculateCircleCenterWithOffset(playerData.Position, currentRadius, playerData.obfv_CachedOffsetMultiplier, playerData.obfv_CachedOffsetAngle);
			obfv_m_MarkerManager.obfm_AddCircle(circleCenter, currentRadius, circleColor, hideWhenNested, priority);
		}
		obfv_m_MarkerManager.Update();
	}
	void obfm_TriggerUpdate()
	{
		if (!obfv_m_MapWidget || !obfv_m_MarkerManager)
			return;
		obfv_m_MarkerManager.obfm_UpdateOffsets();
		obfv_m_MarkerManager.Update();
	}
	void obfm_UpdateOffsets()
	{
		if (obfv_m_MarkerManager)
			obfv_m_MarkerManager.obfm_UpdateOffsets();
	}
	void obfm_ClearMap()
	{
		if (obfv_m_DrawCanvas)
		{
			obfv_m_DrawCanvas.Clear();
			obfv_m_DrawCanvas.Unlink();
			obfv_m_DrawCanvas = null;
		}
		if (obfv_m_MarkerManager)
			obfv_m_MarkerManager.obfm_ClearMarkers();
	}
	private vector obfm_CalculateCircleCenterWithOffset(vector playerPosition, float currentRadius, float cachedMultiplier, float cachedAngle)
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
	void obfm_DrawBountyCircle(vector center, float obfv_radius, int color, bool hideWhenNested = false, int priority = 1)
	{
		if (!obfv_m_MarkerManager)
			return;
		obfv_m_MarkerManager.obfm_AddCircle(center, obfv_radius, color, hideWhenNested, priority);
	}
	void obfm_ClearAll()
	{
		if (obfv_m_MarkerManager)
		{
			obfv_m_MarkerManager.obfm_ClearMarkers();
		}
	}
	bool obfm_HasMarkers()
	{
		if (obfv_m_MarkerManager)
		{
			return obfv_m_MarkerManager.obfm_HasMarkers();
		}
		return false;
	}
}