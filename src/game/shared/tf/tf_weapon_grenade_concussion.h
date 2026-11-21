//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose: TF Concussion Grenade.
//
//=============================================================================//
#ifndef TF_WEAPON_GRENADE_CONCUSSION_H
#define TF_WEAPON_GRENADE_CONCUSSION_H
#ifdef _WIN32
#pragma once
#endif

#include "tf_weaponbase_grenade.h"
#include "tf_weaponbase_grenadeproj.h"

// Client specific.
#ifdef CLIENT_DLL
#define CTFGrenadeConcussion C_TFGrenadeConcussion
#endif

//=============================================================================
//
// TF Concussion Grenade
//
class CTFGrenadeConcussion : public CTFWeaponBaseGrenade
{
public:

	DECLARE_CLASS( CTFGrenadeConcussion, CTFWeaponBaseGrenade );
	DECLARE_NETWORKCLASS();
	DECLARE_PREDICTABLE();

	// Overrides.
	virtual void	Spawn();
	virtual void	Precache();
	virtual void	Explode(trace_t* pTrace, int bitsDamageType);
	virtual void	ItemPostFrame();
	virtual void	HideThink(void) { SetWeaponVisible(false); }
	virtual bool	ShouldDraw();
	virtual bool	Deploy();

	CTFGrenadeConcussion() {}

	// Unique identifier.
	virtual int			GetWeaponID( void ) const			{ return TF_WEAPON_GRENADE_CONCUSSION; }

// Server specific.
#ifdef GAME_DLL

	DECLARE_DATADESC();

	virtual CTFWeaponBaseGrenadeProj *EmitGrenade( Vector vecSrc, QAngle vecAngles, Vector vecVel, AngularImpulse angImpulse, CBasePlayer *pPlayer, float flTime, int iflags = 0 );

#endif

	CTFGrenadeConcussion( const CTFGrenadeConcussion & ) {}
};

//=============================================================================
//
// TF Concussion Grenade Projectile (Server specific.)
//
#ifdef GAME_DLL

class CTFGrenadeConcussionProjectile : public CTFWeaponBaseGrenadeProj
{
public:

	DECLARE_CLASS( CTFGrenadeConcussionProjectile, CTFWeaponBaseGrenadeProj );
	DECLARE_NETWORKCLASS();

	// Unique identifier.
	virtual int			GetWeaponID( void ) const			{ return TF_WEAPON_GRENADE_CONCUSSION; }

	// Creation.
	static CTFGrenadeConcussionProjectile *Create( const Vector &position, const QAngle &angles, const Vector &velocity, 
		                                       const AngularImpulse &angVelocity, CBaseCombatCharacter *pOwner, const CTFWeaponInfo &weaponInfo, float timer, int iFlags = 0 );

	// Overrides.
	virtual void	Spawn();
	virtual void	Precache();
	virtual void	BounceSound( void );
	virtual void	Explode( trace_t *pTrace, int bitsDamageType );
	virtual void	Detonate();
	virtual void	ItemPostFrame();
	void			DrawRadius( float fl_DmgRadius );
	void			SendDispatchEffect();
	void			RemoveGrenade();

#ifdef CLIENT_DLL

	bool					ShouldDraw(void);
	// Server specific.
#else

	DECLARE_DATADESC();

	virtual void			HandleAnimEvent(animevent_t* pEvent);

	// Each derived grenade class implements this.
	virtual CTFWeaponBaseGrenadeProj* EmitGrenade(Vector vecSrc, QAngle vecAngles, Vector vecVel, AngularImpulse angImpulse, CBasePlayer* pPlayer, float flTime, int iflags = 0);

#endif

private:

	float m_flDetonateTime;
};

#endif

#endif // TF_WEAPON_GRENADE_CONCUSSION_H
