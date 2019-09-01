#include <a_samp>
#include "includes/streamer.inc"

public OnFilterScriptInit()
{
	print("\n---Wczytywanie obiektów---");
	LoadObjects();

	return 1;
}
public OnFilterScriptExit()
{
	return 1;
}
LoadObjects()
{
	//blokada pay'n'spray
	{
		CreateDynamicObject(973, 1359.3059, -1722.1389, 13.4493, 0.0000, 0.0000, 180.0000);
		CreateDynamicObject(971, 2071.5358, -1831.6967, 12.9636, 0.0000, 0.0000, 90.0000);
		CreateDynamicObject(971, 1042.9864, -1025.9786, 30.8041, 0.0000, 0.0000, 0.0000);
		CreateDynamicObject(973, 1362.8630, -1592.3475, 13.4323, 0.0000, 0.0000, -15.7999);
		CreateDynamicObject(973, 1368.1082, -1573.8111, 13.3524, 0.0000, 0.0000, 163.9998);
		CreateDynamicObject(973, 1401.7467, -1450.6262, 13.3332, 0.0000, 0.0000, 0.0000);
		CreateDynamicObject(971, 489.0516, -1735.2194, 11.2483, 0.0000, 0.0000, -10.1999);
		CreateDynamicObject(971, -1905.1223, 277.7148, 42.4727, 0.0000, 0.0000, 0.0000);
		CreateDynamicObject(971, -2425.3256, 1028.1572, 51.8174, 0.0000, 0.0000, 0.0000);
		CreateDynamicObject(971, 1968.4189, 2162.2370, 10.9817, 0.0000, 0.0000, 90.0000);
		CreateDynamicObject(971, -100.1354, 1111.5255, 21.0765, 0.0000, 0.0000, 0.0000);
		CreateDynamicObject(971, 719.9442, -462.5256, 15.7359, 0.0000, 0.0000, 0.0000);
		CreateDynamicObject(971, -1420.7375, 2590.9916, 57.1839, 0.0000, 0.0000, 0.0000);
		CreateDynamicObject(971, -1935.8690, 239.5274, 34.0799, 0.0000, 0.0000, 0.0000);
		CreateDynamicObject(971, -2716.3447, 217.7675, 3.9682, 0.0000, 0.0000, 90.0000);
		CreateDynamicObject(8167, 2645.9768, -2039.2774, 13.0988, 0.0000, 0.0000, 90.0000);
		CreateDynamicObject(8167, 2645.9768, -2039.2874, 15.2688, 0.0000, 0.0000, 90.0000);
		CreateDynamicObject(971, 1024.8555, -1029.3911, 31.8047, 0.0000, 0.0000, 0.0000);
		CreateDynamicObject(971, 2387.2949, 1043.5672, 9.9948, 0.0000, 0.0000, 0.0000);
		CreateDynamicObject(8167, 1843.1953, -1856.2824, 12.2801, 0.0000, 0.0000, 0.0000);
		CreateDynamicObject(8167, 1843.1953, -1856.2915, 14.6901, 0.0000, 0.0000, 0.0000);
		CreateDynamicObject(8167, 2006.7484, 2317.7934, 10.1742, 0.0000, 0.0000, 90.0000);
		CreateDynamicObject(8167, 2006.7484, 2317.7934, 12.5542, 0.0000, 0.0000, 90.0000);
		CreateDynamicObject(8167, 2005.3341, 2303.4252, 10.1702, 0.0000, 0.0000, 270.0000);
		CreateDynamicObject(8167, 2005.3341, 2303.4252, 12.5702, 0.0000, 0.0000, 270.0000);
		CreateDynamicObject(971, -1787.4119, 1209.4625, 24.7200, 0.0000, 0.0000, 0.0000);
	}
	

	return 1;
}



