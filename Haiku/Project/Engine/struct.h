#pragma once


// 3���� ������ ��ġ�Ǵ� ����
struct Vtx
{
	Vec3 vPos;		 // ������ ��ǥ	
	Vec4 vColor;	 // ������ ���� ����
	Vec2 vUV;		 // UV ��ǥ�� or Texture Coodinate
};

struct tDebugShapeInfo
{
	DEBUG_SHAPE	eShape;

	Vec3		vWorldPos;
	Vec3		vWorldScale;
	Vec3		vWorldRot;
	Matrix		matWorld;

	Vec3		vColor;
	float		fLifeTime;
	float		fDuration;
	bool		bDepthTest;
};


struct tLightInfo
{
	Vec4	vColor;		// ���� ����	- ������ ���� ����
	Vec4	vSpecular;	// �ݻ籤	- ������ ��ü ǥ���� �ݻ�� ����
	Vec4	vAmbient;	// ȯ�汤(�ֺ���) - ������ ���ؼ� ����Ǵ� �ּ����� ��

	Vec3	vWorldPos;	// ������ ��ġ
	Vec3	vWorldDir;	// ������ ���ϴ� ����
	float	fRadius;	// ������ ���� �ݰ�, �Ÿ� ����
	float	fAngle;		// ������ ���� ����

	int		LightType;	// ���� Ÿ��

	Vec3	vPadding;
};

struct tPixel
{
	BYTE r, g, b, a;
};

struct tParticle
{
	Vec4	vLocalPos;		// ���� ��ġ
	Vec4	vWorldPos;		// ���� ��ġ
	Vec4	vWorldInitScale;// �ʱ� ũ��
	Vec4	vWorldScale;	// ũ��
	Vec4	vWorldRotation;	// ȸ����
	Vec3	vVelocity;		// �ӵ�
	Vec4	vColor;			// ����
	Vec4	vForce;			// ���ڿ� ����� ���� �� �ѷ�
	Vec3	vNoiseForce;	// NoiseForce ���� ���� ���� ��
	float	NoiseForceTime;	// NoiseForce �� ���ù��� �ð�

	float	NormalizeAge;	// Age �� Life �������� ����ȭ�� ��
	float	Mass;			// ����
	float	Age;			// ���� ����
	float	Life;			// ����
	int		Active;			// Ȱ��ȭ, ��Ȱ��ȭ ����
};

struct tParticleModule
{
	// Sapwn ���
	Vec4	vSpawnColor;	// �ʱ� �÷�
	Vec4	vSpawnMinScale;	// �ʱ� �ּ� ũ��
	Vec4	vSpawnMaxScale;	// �ʱ� �ִ� ũ��	

	float	MinLife;		// �ּ� ����
	float	MaxLife;		// �ִ� ����
	float	MinMass;		// �ּ� ����
	float	MaxMass;		// �ִ� ����
	int		SpawnRate;		// �ʴ� ���� ����
	int		SpaceType;		// ��ǥ��(0 : LocalSpace, 1 : WorldSpace)
	int		SpawnShape;		// ���� ����(0 : Sphere, 1 : Box)
	float	Radius;			// SpawnShape �� Sphere �� ���, ������ ����
	Vec4	vSpawnBoxScale;	// SpawnShape �� Box �� ���, Box �� ũ��

	// Add Velocity
	int		AddVelocityType;// 0 : From Center, 1: To Center, 2: Fix Direction
	float	MinSpeed;
	float	MaxSpeed;	
	float	FixedAngle;		// �ش� ���⿡�� �������� ����
	Vec4	FixedDirection;	// ���� ����

	// Scale
	Vec4	vScaleRatio;

	// Noise Force
	float	NoiseForceScale;
	float	NoiseForceTerm;

	// Drag
	float	DragTime;	// ���ӽ�Ű�µ� �ɸ��� �ð�

	// Render
	int		VelocityAlignment;  // 1 : On, 0 : Off
	int		AlphaBasedLife;		// 0 : off, 1 : NomrlizedAge, 2: Age
	float	AlphaMaxAge;

	// Module On / Off
	int arrModuleCheck[(UINT)PARTICLE_MODULE::END];
};

struct tSpawnCount
{
	int	SpawnCount;
	int iPadding[3];
};


// ==================
// ������� ���� ����ü
// ==================
struct tTransform
{
	Matrix	matWorld;
	Matrix	matWorldInv;

	Matrix	matView;
	Matrix	matViewInv;

	Matrix	matProj;
	Matrix	matProjInv;

	Matrix	matWV;
	Matrix	matWVP;
};
extern tTransform g_Transform;

struct tMtrlConst
{
	int iArr[4];
	float fArr[4];
	Vec2 v2Arr[4];
	Vec4 v4Arr[4];
	Matrix matArr[4];
	int	bTex[(UINT)TEX_PARAM::END];
	int iPadding[2];
};

struct tAnimData2D
{
	Vec2 vLeftTop;
	Vec2 vSlizeSize;
	Vec2 vBackGround;
	Vec2 vOffset;
	int  UseAnim2D;
	Vec3 vPadding;
};

struct tGlobalData
{
	Vec2	g_RenderResolution;	// ������ �ػ�
	Vec2	g_NoiseTexResolution;
	float	g_dt;				// Delta Time
	float	g_time;				// ���� �ð�
	int		g_Light2DCount;		// 2D ���� ����
	int		g_Light3DCount;		// 3D ���� ����	
};
extern tGlobalData g_global;