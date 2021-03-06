/*	SCCS Id: @(#)obj.h	3.4	2002/01/07	*/
/* Copyright (c) Stichting Mathematisch Centrum, Amsterdam, 1985. */
/* NetHack may be freely redistributed.  See license for details. */

#ifndef OBJ_H
#define OBJ_H

/* #define obj obj_nh */ /* uncomment for SCO UNIX, which has a conflicting
			  * typedef for "obj" in <sys/types.h> */

union vptrs {
	    struct obj *v_nexthere;	/* floor location lists */
	    struct obj *v_ocontainer;	/* point back to container */
	    struct monst *v_ocarry;	/* point back to carrying monst */
};

struct obj {
	struct obj *nobj;
	union vptrs v;
#define nexthere	v.v_nexthere
#define ocontainer	v.v_ocontainer
#define ocarry		v.v_ocarry

	struct obj *cobj;	/* contents list for containers */
	unsigned o_id;
	xchar ox,oy;
	/*short*/long otyp;		/* object class number */
	/*short*/long oldtyp;	/* WAC for unpolymorph */
	unsigned owt;
	long quan;		/* number of items */

	schar spe;		/* quality of weapon, armor or ring (+ or -)
				   number of charges for wand ( >= -1 )
				   marks your eggs, spinach tins
				   royal coffers for a court ( == 2)
				   tells which fruit a fruit is
				   special for uball and amulet
				   historic and gender for statues */
#define STATUE_HISTORIC 0x01
#define STATUE_MALE     0x02
#define STATUE_FEMALE   0x04
	char	oclass;		/* object class */
	char	invlet;		/* designation in inventory */
	/*char*/int	oartifact;	/* artifact array index */
	boolean fakeartifact;	/* so the player cannot rename them */
	schar 	altmode; 	/* alternate modes - eg. SMG, double Lightsaber */
				/* WP_MODEs are in decreasing speed */
#define WP_MODE_AUTO	0	/* Max firing speed */
#define WP_MODE_BURST	1	/* 1/3 of max rate */
#define WP_MODE_SINGLE 	2	/* Single shot */

	xchar where;		/* where the object thinks it is */
#define OBJ_FREE	0		/* object not attached to anything */
#define OBJ_FLOOR	1		/* object on floor */
#define OBJ_CONTAINED	2		/* object in a container */
#define OBJ_INVENT	3		/* object in the hero's inventory */
#define OBJ_MINVENT	4		/* object in a monster inventory */
#define OBJ_MIGRATING	5		/* object sent off to another level */
#define OBJ_BURIED	6		/* object buried */
#define OBJ_ONBILL	7		/* object on shk bill */
#define NOBJ_STATES	8
	xchar timed;		/* # of fuses (timers) attached to this obj */

	Bitfield(cursed,1);
	Bitfield(blessed,1);
	Bitfield(hvycurse,1);	/* harder to uncurse than "regular" cursed items --Amy */
	Bitfield(prmcurse,1);
	Bitfield(morgcurse,1);	/* Ancient Morgothian curse */
	Bitfield(evilcurse,1);	/* Topi Ylinen curse */
	Bitfield(bbrcurse,1);	/* Black Breath curse */
	Bitfield(stckcurse,1);	/* sticky curse - resists certain methods of getting the item off --Amy */
	Bitfield(unpaid,1);	/* on some bill */
	Bitfield(no_charge,1);	/* if shk shouldn't charge for this */
	Bitfield(known,1);	/* exact nature known */
	Bitfield(dknown,1);	/* color or text known */
	Bitfield(bknown,1);	/* blessing or curse known */
	Bitfield(rknown,1);	/* rustproof or not known */
	Bitfield(petmarked,1);	/* pets will not drop this --Amy */

	Bitfield(oeroded,2);	/* rusted/burnt weapon/armor */
	Bitfield(oeroded2,2);	/* corroded/rotted weapon/armor */
#define greatest_erosion(otmp) (int)((otmp)->oeroded > (otmp)->oeroded2 ? (otmp)->oeroded : (otmp)->oeroded2)

#define greatest_erosionX(otmp) (int) (objects[(otmp)->otyp].oc_material == COMPOST ? (otmp)->oeroded : ((otmp)->oeroded > (otmp)->oeroded2 ? (otmp)->oeroded : (otmp)->oeroded2))

#define MAX_ERODE 3
#define orotten oeroded		/* rotten food */
#define odiluted oeroded	/* diluted potions */
#define norevive oeroded2
	Bitfield(oerodeproof,1); /* erodeproof weapon/armor */
	Bitfield(olocked,1);	/* object is locked */
#define oarmed olocked
#define odrained olocked	/* drained corpse */
	Bitfield(obroken,1);	/* lock has been broken */
	Bitfield(otrapped,1);	/* container is trapped */
				/* or accidental tripped rolling boulder trap */
#define opoisoned otrapped	/* object (weapon) is coated with poison */

	Bitfield(recharged,3);	/* number of times it's been recharged */
	Bitfield(lamplit,1);	/* a light-source -- can be lit */
	Bitfield(oinvis,1);	/* invisible */
	Bitfield(oinvisreal,1);	/* really invisible - won't be visible even with see invis --Amy */
	Bitfield(greased,2);	/* covered with grease */
	Bitfield(oattached,2);	/* obj struct has special attachment */
#define OATTACHED_NOTHING 0
#define OATTACHED_MONST   1	/* monst struct in oextra */
#define OATTACHED_M_ID    2	/* monst id in oextra */
#define OATTACHED_UNUSED3 3
	Bitfield(in_use,1);	/* for magic items before useup items */
	Bitfield(bypass,1);	/* mark this as an object to be skipped by bhito() */

	Bitfield(yours,1);	/* obj is yours (eg. thrown by you) */
	Bitfield(was_thrown,1); /* thrown by the hero since last picked up */
	Bitfield(mstartinvent,1); /* item is part of a monster's starting inventory --Amy */
	Bitfield(mstartinventB,1);
	/* ? free bits */

	int	corpsenm;	/* type of corpse is mons[corpsenm] */
#define leashmon  corpsenm	/* gets m_id of attached pet */
#define spestudied corpsenm	/* # of times a spellbook has been studied */
#define fromsink  corpsenm	/* a potion from a sink */

#ifdef RECORD_ACHIEVE
#define record_achieve_special corpsenm
#endif
	int enchantment;	/* in case of armors, special property --Amy */

	unsigned oeaten;	/* nutrition left in food, if partly eaten */
	long age;		/* creation date */

	int shirtmessage;	/* o_id is not random enough for me. --Amy */

	uchar onamelth;		/* length of name (following oxlth) */
	Bitfield(selfmade,1);	/* made with chemistry set or magic marker */
	/*short*/long oxlth;		/* length of following data */
	/* in order to prevent alignment problems oextra should
	   be (or follow) a long int */
	long owornmask;
	long oextra[1];		/* used for name of ordinary objects - length
				   is flexible; amount for tmp gold objects */
};

#define newobj(xl)	(struct obj *)alloc((unsigned)(xl) + sizeof(struct obj))
#define ONAME(otmp)	(((char *)(otmp)->oextra) + (otmp)->oxlth)

/* All objects */
#define is_hazy(otmp)	((otmp)->oldtyp != STRANGE_OBJECT)
/* [ALI] None of the objects listed here can be picked up by normal monsters.
 * If any such objects need to be marked as indestructible then consideration
 * will need to be given to what happens when such a monster disappears
 * carrying the object.
 */
#define evades_destruction(otmp) ( \
			(otmp)->otyp == AMULET_OF_YENDOR || \
			(otmp)->otyp == CANDELABRUM_OF_INVOCATION || \
			(otmp)->otyp == BELL_OF_OPENING || \
			(otmp)->otyp == SPE_BOOK_OF_THE_DEAD || \
			(otmp)->oartifact == ART_KEY_OF_LAW || \
			(otmp)->oartifact == ART_KEY_OF_NEUTRALITY || \
			(otmp)->oartifact == ART_KEY_OF_CHAOS)
#define always_visible(otmp) ( \
			(otmp)->otyp == MUMMY_WRAPPING || \
			(otmp)->oclass == COIN_CLASS)

/* Weapons and weapon-tools */
/* KMH -- now based on skill categories.  Formerly:
 *	#define is_sword(otmp)	(otmp->oclass == WEAPON_CLASS && \
 *			 objects[otmp->otyp].oc_wepcat == WEP_SWORD)
 *	#define is_blade(otmp)	(otmp->oclass == WEAPON_CLASS && \
 *			 (objects[otmp->otyp].oc_wepcat == WEP_BLADE || \
 *			  objects[otmp->otyp].oc_wepcat == WEP_SWORD))
 *	#define is_weptool(o)	((o)->oclass == TOOL_CLASS && \
 *			 objects[(o)->otyp].oc_weptool)
 *	#define is_multigen(otyp) (otyp <= SHURIKEN)
 *	#define is_poisonable(otyp) (otyp <= BEC_DE_CORBIN)
 */

#define is_sword(otmp)	((otmp)->oclass == WEAPON_CLASS && \
			 objects[(otmp)->otyp].oc_skill >= P_SHORT_SWORD && \
			 objects[(otmp)->otyp].oc_skill <= P_SABER)
#define is_blade(otmp)	((otmp)->oclass == WEAPON_CLASS && \
			 objects[(otmp)->otyp].oc_skill >= P_DAGGER && \
			 objects[(otmp)->otyp].oc_skill <= P_SABER)
#define is_pole(otmp)	(((otmp)->oclass == WEAPON_CLASS || \
			(otmp)->oclass == TOOL_CLASS) && \
			 (objects[(otmp)->otyp].oc_skill == P_POLEARMS || \
			 objects[(otmp)->otyp].oc_skill == P_LANCE))
#define is_spear(otmp)	((otmp)->oclass == WEAPON_CLASS && \
			 objects[(otmp)->otyp].oc_skill >= P_SPEAR && \
			 objects[(otmp)->otyp].oc_skill <= P_JAVELIN)
#define is_axe(otmp)	((otmp)->oclass == WEAPON_CLASS && \
			 objects[(otmp)->otyp].oc_skill == P_AXE)
#define is_launcher(otmp)	((otmp)->oclass == WEAPON_CLASS && \
			 objects[(otmp)->otyp].oc_skill >= P_BOW && \
			 objects[(otmp)->otyp].oc_skill <= P_CROSSBOW)
#define is_ammo(otmp)	(((otmp)->oclass == WEAPON_CLASS || \
			 (otmp)->oclass == GEM_CLASS) && \
			 objects[(otmp)->otyp].oc_skill >= -P_CROSSBOW && \
			 objects[(otmp)->otyp].oc_skill <= -P_BOW)
#define is_missile(otmp)	(((otmp)->oclass == WEAPON_CLASS || \
			 (otmp)->oclass == TOOL_CLASS) && \
			 objects[(otmp)->otyp].oc_skill >= -P_BOOMERANG && \
			 objects[(otmp)->otyp].oc_skill <= -P_DART)
#define is_grenade(otmp)	(is_ammo(otmp) && \
			 	 objects[(otmp)->otyp].w_ammotyp == WP_GRENADE)
#define is_multigen(otmp)	((otmp)->oclass == WEAPON_CLASS && \
			 objects[(otmp)->otyp].oc_skill >= -P_SHURIKEN && \
			 objects[(otmp)->otyp].oc_skill <= -P_BOW)
#define is_lower_multigen(otmp)	((otmp)->oclass == WEAPON_CLASS && \
			 (objects[(otmp)->otyp].oc_skill == -P_BOOMERANG || objects[(otmp)->otyp].oc_skill == P_BOOMERANG || objects[(otmp)->otyp].oc_skill == P_SPEAR || objects[(otmp)->otyp].oc_skill == P_DAGGER || objects[(otmp)->otyp].oc_skill == P_KNIFE || objects[(otmp)->otyp].oc_skill == P_JAVELIN ) )
#define is_unpoisonable_firearm_ammo(otmp)	\
			 (is_bullet(otmp) || (otmp)->otyp == STICK_OF_DYNAMITE)
#define is_poisonable(otmp)	((otmp)->oclass == WEAPON_CLASS && \
			 (objects[(otmp)->otyp].oc_skill <= P_SABER || \
			 (objects[(otmp)->otyp].oc_skill >= P_POLEARMS && \
			 objects[(otmp)->otyp].oc_skill <= P_LANCE)) && \
			 !is_unpoisonable_firearm_ammo(otmp))
#define uslinging()	(uwep && objects[uwep->otyp].oc_skill == P_SLING)
#define is_weptool(o)	((o)->oclass == TOOL_CLASS && \
			 objects[(o)->otyp].oc_skill != P_NONE)
#define is_pick(otmp)	(((otmp)->oclass == WEAPON_CLASS || \
			 (otmp)->oclass == TOOL_CLASS) && \
			 objects[(otmp)->otyp].oc_skill == P_PICK_AXE)
#define is_antibar(otmp)	((otmp)->otyp == ELECTRIC_SWORD || (otmp)->otyp == GOLDEN_SABER || (otmp)->otyp == PLATINUM_SABER  || (otmp)->otyp == METAL_CLUB  || (otmp)->otyp == RADIOACTIVE_DAGGER  || (otmp)->otyp == ETERNIUM_BLADE  || (otmp)->otyp == DEVIL_STAR  || (otmp)->otyp == OBSID  || (otmp)->otyp == IMPACT_STAFF  || (otmp)->otyp == SOFT_LADY_SHOE  || (otmp)->otyp == INKA_BOOT  || (otmp)->otyp == BRIDGE_MUZZLE  || (otmp)->otyp == MALLET  || (otmp)->otyp == YATAGAN  || (otmp)->otyp == WEDGED_LITTLE_GIRL_SANDAL  || (otmp)->otyp == HUGGING_BOOT || (otmp)->otyp == DIAMOND_SMASHER  || (otmp)->otyp == BLOCK_HEELED_COMBAT_BOOT  || (otmp)->otyp == HIGH_HEELED_SANDAL  || (otmp)->otyp == SEXY_LEATHER_PUMP  || (otmp)->otyp == TORPEDO  || (otmp)->otyp == HOMING_TORPEDO  || (otmp)->otyp == STEEL_WHIP  )

#define ammo_and_launcher(otmp,ltmp) \
			(is_ammo(otmp) && (ltmp) && \
			objects[(otmp)->otyp].oc_skill == -objects[(ltmp)->otyp].oc_skill && \
			  objects[(otmp)->otyp].w_ammotyp == objects[(ltmp)->otyp].w_ammotyp)
#define bimanual(otmp)	(((otmp)->oclass == WEAPON_CLASS || \
			  (otmp)->oclass == TOOL_CLASS) && \
			 objects[(otmp)->otyp].oc_bimanual)

#define is_lightsaber(otmp) (objects[(otmp)->otyp].oc_skill == P_LIGHTSABER || (otmp)->otyp == LASER_SWATTER)

#define is_firearm(otmp) \
			((otmp)->oclass == WEAPON_CLASS && \
			 objects[(otmp)->otyp].oc_skill == P_FIREARM)
#define is_bullet(otmp)	((otmp)->oclass == WEAPON_CLASS && \
			 objects[(otmp)->otyp].oc_skill == -P_FIREARM)

/* Armor */
#define is_shield(otmp) ((otmp)->oclass == ARMOR_CLASS && \
			 objects[(otmp)->otyp].oc_armcat == ARM_SHIELD)
#define is_helmet(otmp) ((otmp)->oclass == ARMOR_CLASS && \
			 objects[(otmp)->otyp].oc_armcat == ARM_HELM)
#define is_boots(otmp)	((otmp)->oclass == ARMOR_CLASS && \
			 objects[(otmp)->otyp].oc_armcat == ARM_BOOTS)
#define is_gloves(otmp) ((otmp)->oclass == ARMOR_CLASS && \
			 objects[(otmp)->otyp].oc_armcat == ARM_GLOVES)
#define is_cloak(otmp)	((otmp)->oclass == ARMOR_CLASS && \
			 objects[(otmp)->otyp].oc_armcat == ARM_CLOAK)
#define is_shirt(otmp)	((otmp)->oclass == ARMOR_CLASS && \
			 objects[(otmp)->otyp].oc_armcat == ARM_SHIRT)
#define is_suit(otmp)	((otmp)->oclass == ARMOR_CLASS && \
			 objects[(otmp)->otyp].oc_armcat == ARM_SUIT)
#define is_droven_armor(otmp)	((otmp)->otyp == DROVEN_HELM\
				|| (otmp)->otyp == DROVEN_PLATE_MAIL\
				|| (otmp)->otyp == DROVEN_CHAIN_MAIL\
				|| (otmp)->otyp == DROVEN_MITHRIL_COAT\
				|| (otmp)->otyp == DROVEN_CLOAK)
#define is_elven_armor(otmp)	((otmp)->otyp == ELVEN_LEATHER_HELM\
				|| (otmp)->otyp == ELVEN_MITHRIL_COAT\
				|| (otmp)->otyp == ELVEN_CLOAK\
				|| (otmp)->otyp == ELVEN_GAUNTLETS\
				|| (otmp)->otyp == ELVEN_HELM\
				|| (otmp)->otyp == HIGH_ELVEN_HELM\
				|| (otmp)->otyp == ELVEN_TOGA\
				|| (otmp)->otyp == ELVEN_SHIELD\
				|| (otmp)->otyp == ELVEN_BOOTS)
#define is_orcish_armor(otmp)	((otmp)->otyp == ORCISH_HELM\
				|| (otmp)->otyp == ORCISH_CHAIN_MAIL\
				|| (otmp)->otyp == ORCISH_RING_MAIL\
				|| (otmp)->otyp == ORCISH_CLOAK\
				|| (otmp)->otyp == URUK_HAI_SHIELD\
				|| (otmp)->otyp == ORCISH_GUARD_SHIELD\
				|| (otmp)->otyp == ORCISH_SHIELD)
#define is_dwarvish_armor(otmp)	((otmp)->otyp == DWARVISH_IRON_HELM\
				|| (otmp)->otyp == DWARVISH_MITHRIL_COAT\
				|| (otmp)->otyp == DWARVISH_CLOAK\
				|| (otmp)->otyp == DWARVISH_ROUNDSHIELD)
#define is_gnomish_armor(otmp)	(FALSE)

#define is_musable(otmp)	((otmp)->otyp == SCR_TELEPORTATION\
|| (otmp)->otyp == POT_HEALING\
|| (otmp)->otyp == POT_CURE_WOUNDS\
|| (otmp)->otyp == POT_CURE_SERIOUS_WOUNDS\
|| (otmp)->otyp == POT_CURE_CRITICAL_WOUNDS\
|| (otmp)->otyp == POT_EXTRA_HEALING\
|| (otmp)->otyp == WAN_DIGGING\
|| (otmp)->otyp == WAN_CREATE_MONSTER\
|| (otmp)->otyp == SCR_CREATE_MONSTER\
|| (otmp)->otyp == SCR_CREATE_VICTIM\
|| (otmp)->otyp == WAN_TELEPORTATION\
|| (otmp)->otyp == POT_FULL_HEALING\
|| (otmp)->otyp == WAN_HEALING\
|| (otmp)->otyp == WAN_EXTRA_HEALING\
|| (otmp)->otyp == WAN_CREATE_HORDE\
|| (otmp)->otyp == POT_VAMPIRE_BLOOD\
|| (otmp)->otyp == WAN_FULL_HEALING\
|| (otmp)->otyp == SCR_TELE_LEVEL\
|| (otmp)->otyp == WAN_TELE_LEVEL\
|| (otmp)->otyp == SCR_ROOT_PASSWORD_DETECTION\
|| (otmp)->otyp == RIN_TIMELY_BACKUP\
|| (otmp)->otyp == SCR_SUMMON_UNDEAD\
|| (otmp)->otyp == WAN_SUMMON_UNDEAD\
|| (otmp)->otyp == SCR_HEALING\
|| (otmp)->otyp == SCR_EXTRA_HEALING\
|| (otmp)->otyp == SCR_POWER_HEALING\
|| (otmp)->otyp == SCR_WARPING\
|| (otmp)->otyp == WAN_DEATH\
|| (otmp)->otyp == WAN_SLEEP\
|| (otmp)->otyp == WAN_FIREBALL\
|| (otmp)->otyp == WAN_FIRE\
|| (otmp)->otyp == WAN_COLD\
|| (otmp)->otyp == WAN_LIGHTNING\
|| (otmp)->otyp == WAN_MAGIC_MISSILE\
|| (otmp)->otyp == WAN_STRIKING\
|| (otmp)->otyp == SCR_FIRE\
|| (otmp)->otyp == POT_PARALYSIS\
|| (otmp)->otyp == POT_BLINDNESS\
|| (otmp)->otyp == POT_CONFUSION\
|| (otmp)->otyp == POT_SLEEPING\
|| (otmp)->otyp == POT_ACID\
|| (otmp)->otyp == FROST_HORN\
|| (otmp)->otyp == FIRE_HORN\
|| (otmp)->otyp == TEMPEST_HORN\
|| (otmp)->otyp == WAN_DRAINING\
|| (otmp)->otyp == WAN_INCREASE_MAX_HITPOINTS\
|| (otmp)->otyp == WAN_REDUCE_MAX_HITPOINTS\
|| (otmp)->otyp == SCR_EARTH\
|| (otmp)->otyp == POT_AMNESIA\
|| (otmp)->otyp == WAN_CANCELLATION\
|| (otmp)->otyp == POT_CYANIDE\
|| (otmp)->otyp == POT_RADIUM\
|| (otmp)->otyp == WAN_ACID\
|| (otmp)->otyp == SCR_TRAP_CREATION\
|| (otmp)->otyp == SCR_CREATE_TRAP\
|| (otmp)->otyp == WAN_TRAP_CREATION\
|| (otmp)->otyp == SCR_FLOOD\
|| (otmp)->otyp == SCR_LAVA\
|| (otmp)->otyp == SCR_GROWTH\
|| (otmp)->otyp == SCR_ICE\
|| (otmp)->otyp == SCR_CLOUDS\
|| (otmp)->otyp == SCR_BARRHING\
|| (otmp)->otyp == WAN_SOLAR_BEAM\
|| (otmp)->otyp == WAN_POISON\
|| (otmp)->otyp == SCR_LOCKOUT\
|| (otmp)->otyp == WAN_BANISHMENT\
|| (otmp)->otyp == POT_HALLUCINATION\
|| (otmp)->otyp == POT_ICE\
|| (otmp)->otyp == POT_STUNNING\
|| (otmp)->otyp == POT_NUMBNESS\
|| (otmp)->otyp == POT_URINE\
|| (otmp)->otyp == POT_CANCELLATION\
|| (otmp)->otyp == POT_SLIME\
|| (otmp)->otyp == SCR_BAD_EFFECT\
|| (otmp)->otyp == WAN_BAD_EFFECT\
|| (otmp)->otyp == POT_FIRE\
|| (otmp)->otyp == POT_DIMNESS\
|| (otmp)->otyp == WAN_SLOW_MONSTER\
|| (otmp)->otyp == WAN_FEAR\
|| (otmp)->otyp == POT_FEAR\
|| (otmp)->otyp == POT_GAIN_LEVEL\
|| (otmp)->otyp == WAN_GAIN_LEVEL\
|| (otmp)->otyp == WAN_MAKE_INVISIBLE\
|| (otmp)->otyp == POT_INVISIBILITY\
|| (otmp)->otyp == WAN_POLYMORPH\
|| (otmp)->otyp == WAN_MUTATION\
|| (otmp)->otyp == POT_SPEED\
|| (otmp)->otyp == WAN_SPEED_MONSTER\
|| (otmp)->otyp == POT_POLYMORPH\
|| (otmp)->otyp == POT_MUTATION\
|| (otmp)->otyp == WAN_CLONE_MONSTER\
|| (otmp)->otyp == SCR_DESTROY_ARMOR\
|| (otmp)->otyp == SCR_DESTROY_WEAPON\
|| (otmp)->otyp == SCR_STONING\
|| (otmp)->otyp == SCR_AMNESIA\
|| (otmp)->otyp == BAG_OF_TRICKS\
|| (otmp)->otyp == WAN_STONING\
|| (otmp)->otyp == WAN_DISINTEGRATION\
|| (otmp)->otyp == WAN_PARALYSIS\
|| (otmp)->otyp == WAN_CURSE_ITEMS\
|| (otmp)->otyp == WAN_AMNESIA\
|| (otmp)->otyp == WAN_LEVITATION\
|| (otmp)->otyp == WAN_PSYBEAM\
|| (otmp)->otyp == WAN_HYPER_BEAM\
|| (otmp)->otyp == WAN_BAD_LUCK\
|| (otmp)->otyp == WAN_REMOVE_RESISTANCE\
|| (otmp)->otyp == WAN_CORROSION\
|| (otmp)->otyp == WAN_STARVATION\
|| (otmp)->otyp == WAN_CONFUSION\
|| (otmp)->otyp == WAN_SLIMING\
|| (otmp)->otyp == WAN_LYCANTHROPY\
|| (otmp)->otyp == WAN_FUMBLING\
|| (otmp)->otyp == WAN_PUNISHMENT\
|| (otmp)->otyp == SCR_PUNISHMENT\
|| (otmp)->otyp == WAN_MAKE_VISIBLE\
|| (otmp)->otyp == SCR_SUMMON_BOSS\
|| (otmp)->otyp == SCR_WOUNDS\
|| (otmp)->otyp == SCR_BULLSHIT\
|| (otmp)->otyp == SCR_CHAOS_TERRAIN\
|| (otmp)->otyp == SCR_NASTINESS\
|| (otmp)->otyp == SCR_DEMONOLOGY\
|| (otmp)->otyp == SCR_ELEMENTALISM\
|| (otmp)->otyp == SCR_GIRLINESS\
|| (otmp)->otyp == WAN_SUMMON_SEXY_GIRL\
|| (otmp)->otyp == WAN_DISINTEGRATION_BEAM\
|| (otmp)->otyp == SCR_GROUP_SUMMONING\
|| (otmp)->otyp == WAN_CHROMATIC_BEAM\
|| (otmp)->otyp == WAN_STUN_MONSTER\
|| (otmp)->otyp == SCR_SUMMON_GHOST\
|| (otmp)->otyp == SCR_MEGALOAD\
|| (otmp)->otyp == SCR_VILENESS\
|| (otmp)->otyp == SCR_ENRAGE\
|| (otmp)->otyp == WAN_TIDAL_WAVE\
|| (otmp)->otyp == SCR_ANTIMATTER\
|| (otmp)->otyp == SCR_SUMMON_ELM\
|| (otmp)->otyp == WAN_SUMMON_ELM\
|| (otmp)->otyp == SCR_RELOCATION\
|| (otmp)->otyp == WAN_DRAIN_MANA\
|| (otmp)->otyp == WAN_FINGER_BENDING\
|| (otmp)->otyp == SCR_IMMOBILITY\
|| (otmp)->otyp == WAN_IMMOBILITY\
|| (otmp)->otyp == SCR_FLOODING\
|| (otmp)->otyp == SCR_EGOISM\
|| (otmp)->otyp == WAN_EGOISM\
|| (otmp)->otyp == SCR_RUMOR\
|| (otmp)->otyp == SCR_MESSAGE\
|| (otmp)->otyp == SCR_SIN\
|| (otmp)->otyp == WAN_SIN\
|| (otmp)->otyp == WAN_INERTIA\
|| (otmp)->otyp == WAN_TIME\
|| (otmp)->otyp == WAN_DESLEXIFICATION\
|| (otmp)->otyp == WAN_INFERNO\
|| (otmp)->otyp == WAN_ICE_BEAM\
|| (otmp)->otyp == WAN_THUNDER\
|| (otmp)->otyp == WAN_SLUDGE\
|| (otmp)->otyp == WAN_TOXIC\
|| (otmp)->otyp == WAN_NETHER_BEAM\
|| (otmp)->otyp == WAN_AURORA_BEAM\
|| (otmp)->otyp == WAN_GRAVITY_BEAM\
|| (otmp)->otyp == WAN_CHLOROFORM\
|| (otmp)->otyp == WAN_DREAM_EATER\
|| (otmp)->otyp == WAN_BUBBLEBEAM\
|| (otmp)->otyp == WAN_GOOD_NIGHT\
|| (otmp)->otyp == WAN_HASTE_MONSTER)

/* another butt-ugly macro by Amy... for mkobj.c, whether a musable item may get rerolled */
#define ismusablenumber(number) (number == SCR_TELEPORTATION || number == POT_HEALING || number == POT_CURE_WOUNDS || number == POT_CURE_SERIOUS_WOUNDS || number == POT_CURE_CRITICAL_WOUNDS || number == POT_EXTRA_HEALING || number == WAN_DIGGING || number == WAN_CREATE_MONSTER || number == SCR_CREATE_MONSTER || number == SCR_CREATE_VICTIM || number == WAN_TELEPORTATION || number == POT_FULL_HEALING || number == WAN_HEALING || number == WAN_EXTRA_HEALING || number == WAN_CREATE_HORDE || number == POT_VAMPIRE_BLOOD || number == WAN_FULL_HEALING || number == SCR_TELE_LEVEL || number == WAN_TELE_LEVEL || number == SCR_ROOT_PASSWORD_DETECTION || number == RIN_TIMELY_BACKUP || number == SCR_SUMMON_UNDEAD || number == WAN_SUMMON_UNDEAD || number == SCR_HEALING || number == SCR_EXTRA_HEALING || number == SCR_POWER_HEALING || number == SCR_WARPING || number == WAN_DEATH || number == WAN_SLEEP || number == WAN_FIREBALL || number == WAN_FIRE || number == WAN_COLD || number == WAN_LIGHTNING || number == WAN_MAGIC_MISSILE || number == WAN_STRIKING || number == SCR_FIRE || number == POT_PARALYSIS || number == POT_BLINDNESS || number == POT_CONFUSION || number == POT_SLEEPING || number == POT_ACID || number == FROST_HORN || number == FIRE_HORN || number == TEMPEST_HORN || number == WAN_DRAINING || number == WAN_INCREASE_MAX_HITPOINTS || number == WAN_REDUCE_MAX_HITPOINTS || number == SCR_EARTH || number == POT_AMNESIA || number == WAN_CANCELLATION || number == POT_CYANIDE || number == POT_RADIUM || number == WAN_ACID || number == SCR_TRAP_CREATION || number == SCR_CREATE_TRAP || number == WAN_TRAP_CREATION || number == SCR_FLOOD || number == SCR_LAVA || number == SCR_GROWTH || number == SCR_ICE || number == SCR_CLOUDS || number == SCR_BARRHING || number == WAN_SOLAR_BEAM || number == WAN_POISON || number == SCR_LOCKOUT || number == WAN_BANISHMENT || number == POT_HALLUCINATION || number == POT_ICE || number == POT_STUNNING || number == POT_NUMBNESS || number == POT_URINE || number == POT_CANCELLATION || number == POT_SLIME || number == SCR_BAD_EFFECT || number == WAN_BAD_EFFECT || number == POT_FIRE || number == POT_DIMNESS || number == WAN_SLOW_MONSTER || number == WAN_FEAR || number == POT_FEAR || number == POT_GAIN_LEVEL || number == WAN_GAIN_LEVEL || number == WAN_MAKE_INVISIBLE || number == POT_INVISIBILITY || number == WAN_POLYMORPH || number == WAN_MUTATION || number == POT_SPEED || number == WAN_SPEED_MONSTER || number == POT_POLYMORPH || number == POT_MUTATION || number == WAN_CLONE_MONSTER || number == SCR_DESTROY_ARMOR || number == SCR_DESTROY_WEAPON || number == SCR_STONING || number == SCR_AMNESIA || number == BAG_OF_TRICKS || number == WAN_STONING || number == WAN_DISINTEGRATION || number == WAN_PARALYSIS || number == WAN_CURSE_ITEMS || number == WAN_AMNESIA || number == WAN_LEVITATION || number == WAN_PSYBEAM || number == WAN_HYPER_BEAM || number == WAN_BAD_LUCK || number == WAN_REMOVE_RESISTANCE || number == WAN_CORROSION || number == WAN_STARVATION || number == WAN_CONFUSION || number == WAN_SLIMING || number == WAN_LYCANTHROPY || number == WAN_FUMBLING || number == WAN_PUNISHMENT || number == SCR_PUNISHMENT || number == WAN_MAKE_VISIBLE || number == SCR_SUMMON_BOSS || number == SCR_WOUNDS || number == SCR_BULLSHIT || number == SCR_CHAOS_TERRAIN || number == SCR_NASTINESS || number == SCR_DEMONOLOGY || number == SCR_ELEMENTALISM || number == SCR_GIRLINESS || number == WAN_SUMMON_SEXY_GIRL || number == WAN_DISINTEGRATION_BEAM || number == SCR_GROUP_SUMMONING || number == WAN_CHROMATIC_BEAM || number == WAN_STUN_MONSTER || number == SCR_SUMMON_GHOST || number == SCR_MEGALOAD || number == SCR_VILENESS || number == SCR_ENRAGE || number == WAN_TIDAL_WAVE || number == SCR_ANTIMATTER || number == SCR_SUMMON_ELM || number == WAN_SUMMON_ELM || number == SCR_RELOCATION || number == WAN_DRAIN_MANA || number == WAN_FINGER_BENDING || number == SCR_IMMOBILITY || number == WAN_IMMOBILITY || number == SCR_FLOODING || number == SCR_EGOISM || number == WAN_EGOISM || number == SCR_RUMOR || number == SCR_MESSAGE || number == SCR_SIN || number == WAN_SIN || number == WAN_INERTIA || number == WAN_TIME || number == WAN_DESLEXIFICATION || number == WAN_INFERNO || number == WAN_ICE_BEAM || number == WAN_THUNDER || number == WAN_SLUDGE || number == WAN_TOXIC || number == WAN_NETHER_BEAM || number == WAN_AURORA_BEAM || number == WAN_GRAVITY_BEAM || number == WAN_CHLOROFORM || number == WAN_DREAM_EATER || number == WAN_BUBBLEBEAM || number == WAN_GOOD_NIGHT || number == WAN_HASTE_MONSTER)

/* and yet another one... mkobj.c checks whether a magical and/or non-vanilla piece of armor is rerolled */
#define isvanillaarmor(number) (number == HAWAIIAN_SHIRT || number == T_SHIRT || number == STRIPED_SHIRT || number == PLATE_MAIL || number == RIBBED_PLATE_MAIL || number == PARTIAL_PLATE_MAIL || number == FULL_PLATE_MAIL || number == PLASTEEL_ARMOR || number == CRYSTAL_PLATE_MAIL || number == BRONZE_PLATE_MAIL || number == SPLINT_MAIL || number == METAL_LAMELLAR_ARMOR || number == BANDED_MAIL || number == DWARVISH_MITHRIL_COAT || number == DARK_ELVEN_MITHRIL_COAT || number == ELVEN_MITHRIL_COAT || number == GNOMISH_SUIT || number == CHAIN_MAIL || number == BAR_CHAIN_MAIL || number == BAMBOO_MAIL || number == SILK_MAIL || number == ORCISH_CHAIN_MAIL || number == SCALE_MAIL || number == STUDDED_LEATHER_ARMOR || number == RING_MAIL || number == HEAVY_MAIL || number == ORCISH_RING_MAIL || number == LEATHER_ARMOR || number == LEATHER_JACKET || number == ROBE || number == MUMMY_WRAPPING || number == ORCISH_CLOAK || number == DWARVISH_CLOAK || number == ELVEN_CLOAK || number == LEATHER_CLOAK || number == PLASTEEL_CLOAK || number == ELVEN_LEATHER_HELM || number == GNOMISH_HELM || number == ORCISH_HELM || number == DWARVISH_IRON_HELM || number == FEDORA || number == DENTED_POT || number == HELMET || number == PLASTEEL_GLOVES || number == LEATHER_GLOVES || number == SMALL_SHIELD || number == HEAVY_SHIELD || number == ELVEN_SHIELD || number == URUK_HAI_SHIELD || number == ORCISH_SHIELD || number == LARGE_SHIELD || number == PAPER_SHIELD || number == DWARVISH_ROUNDSHIELD || number == SHIELD || number == LOW_BOOTS || number == IRON_SHOES || number == GNOMISH_BOOTS || number == HIGH_BOOTS)
	
/* Eggs and other food */
#define MAX_EGG_HATCH_TIME 200	/* longest an egg can remain unhatched */
#define stale_egg(egg)	((monstermoves - (egg)->age) > (2*MAX_EGG_HATCH_TIME))
#define ofood(o) ((o)->otyp == CORPSE || (o)->otyp == EGG || (o)->otyp == TIN)
#define polyfodder(obj)	(ofood(obj) && (obj)->corpsenm == PM_CHAMELEON)
#define mlevelgain(obj) (ofood(obj) && (obj)->corpsenm == PM_WRAITH)
#define mhealup(obj)	(ofood(obj) && (obj)->corpsenm == PM_NURSE)
#define drainlevel(corpse) (mons[(corpse)->corpsenm].cnutrit*4/5)

/* Containers */
#define carried(o)	((o)->where == OBJ_INVENT)
#define mcarried(o)	((o)->where == OBJ_MINVENT)
#define Has_contents(o) (/* (Is_container(o) || (o)->otyp == STATUE) && */ \
			 (o)->cobj != (struct obj *)0)
#define Is_container(o) ((o)->otyp == MEDICAL_KIT || \
			 (o)->otyp >= LARGE_BOX && (o)->otyp <= BAG_OF_TRICKS)
#define Is_box(otmp)	((otmp)->otyp == LARGE_BOX || (otmp)->otyp == CHEST || (otmp)->otyp == TREASURE_CHEST || (otmp)->otyp == LARGE_BOX_OF_DIGESTION || (otmp)->otyp == CHEST_OF_HOLDING)
#ifdef WALLET_O_P
#define Is_mbag(otmp)	((otmp)->otyp == BAG_OF_HOLDING || (otmp)->otyp == ICE_BOX_OF_HOLDING || (otmp)->otyp == CHEST_OF_HOLDING || \
                         ((otmp)->oartifact && \
                          ( (otmp)->oartifact == ART_WALLET_OF_PERSEUS || (otmp)->oartifact == ART_PRIAMOS__TREASURE || (otmp)->oartifact == ART_ONE_SIZE_FITS_EVERYTHING) ) || \
  			             (otmp)->otyp == BAG_OF_TRICKS)
#else
#define Is_mbag(otmp)	((otmp)->otyp == BAG_OF_HOLDING || (otmp)->otyp == ICE_BOX_OF_HOLDING || (otmp)->otyp == CHEST_OF_HOLDING || \
  			 (otmp)->otyp == BAG_OF_TRICKS)
#endif

/* dragon gear */
#define Is_dragon_scales(obj)	((obj)->otyp >= GRAY_DRAGON_SCALES && \
				 (obj)->otyp <= YELLOW_DRAGON_SCALES)
#define Is_dragon_mail(obj)	((obj)->otyp >= GRAY_DRAGON_SCALE_MAIL && \
				 (obj)->otyp <= YELLOW_DRAGON_SCALE_MAIL)
#define Is_dragon_armor(obj)	(Is_dragon_scales(obj) || Is_dragon_mail(obj))
#define Dragon_scales_to_pm(obj) &mons[PM_GRAY_DRAGON + (obj)->otyp \
				       - GRAY_DRAGON_SCALES]
#define Dragon_mail_to_pm(obj)	&mons[PM_GRAY_DRAGON + (obj)->otyp \
				      - GRAY_DRAGON_SCALE_MAIL]
#define Dragon_to_scales(pm)	(GRAY_DRAGON_SCALES + (pm - mons))

/* Elven gear */
#define is_elven_weapon(otmp)	((otmp)->otyp == ELVEN_ARROW\
				|| (otmp)->otyp == ELVEN_SPEAR\
				|| (otmp)->otyp == ELVEN_MACE\
				|| (otmp)->otyp == ELVEN_LANCE\
				|| (otmp)->otyp == ELVEN_DAGGER\
				|| (otmp)->otyp == ELVEN_SHORT_SWORD\
				|| (otmp)->otyp == HIGH_ELVEN_WARSWORD\
				|| (otmp)->otyp == ELVEN_BROADSWORD\
				|| (otmp)->otyp == ELVEN_BOW)
#define is_elven_obj(otmp)	(is_elven_armor(otmp) || is_elven_weapon(otmp))

#define is_droven_weapon(otmp)	((otmp)->otyp == DROVEN_ARROW\
				|| (otmp)->otyp == DROVEN_SPEAR\
				|| (otmp)->otyp == DROVEN_LANCE\
				|| (otmp)->otyp == DROVEN_DAGGER\
				|| (otmp)->otyp == DROVEN_SHORT_SWORD\
				|| (otmp)->otyp == DROVEN_GREATSWORD\
				|| (otmp)->otyp == DROVEN_BOW\
				|| (otmp)->otyp == DROVEN_CROSSBOW\
				|| (otmp)->otyp == DROVEN_BOLT)

/* Orcish gear */
#define is_orcish_obj(otmp)	(is_orcish_armor(otmp)\
				|| (otmp)->otyp == ORCISH_ARROW\
				|| (otmp)->otyp == ORCISH_SPEAR\
				|| (otmp)->otyp == ORCISH_DAGGER\
				|| (otmp)->otyp == ORCISH_SHORT_SWORD\
				|| (otmp)->otyp == ORCISH_BOW)

/* Dwarvish gear */
#define is_dwarvish_obj(otmp)	(is_dwarvish_armor(otmp)\
				|| (otmp)->otyp == DWARVISH_SPEAR\
				|| (otmp)->otyp == DWARVISH_BATTLE_AXE\
				|| (otmp)->otyp == DWARVISH_SHORT_SWORD\
				|| (otmp)->otyp == DWARVISH_MATTOCK)

/* Gnomish gear */
#define is_gnomish_obj(otmp)	(is_gnomish_armor(otmp))

/* Light sources */
#define Is_candle(otmp)	((otmp)->otyp == TALLOW_CANDLE || \
			 (otmp)->otyp == WAX_CANDLE || \
			 (otmp)->otyp == JAPAN_WAX_CANDLE || \
			 (otmp)->otyp == OIL_CANDLE || \
			 (otmp)->otyp == GENERAL_CANDLE || \
			 (otmp)->otyp == NATURAL_CANDLE || \
			 (otmp)->otyp == UNSPECIFIED_CANDLE || \
			 (otmp)->otyp == MAGIC_CANDLE || \
			 (otmp)->otyp == UNAFFECTED_CANDLE || \
			 (otmp)->otyp == SPECIFIC_CANDLE || \
			 (otmp)->otyp == __CANDLE)
/* maximum amount of oil in a potion of oil */
#define MAX_OIL_IN_FLASK 400

/* MAGIC_LAMP intentionally excluded below */
/* age field of this is relative age rather than absolute */
#define age_is_relative(otmp)	((otmp)->otyp == BRASS_LANTERN\
				|| (otmp)->otyp == OIL_LAMP\
				|| (otmp)->otyp == TORCH\
				|| (otmp)->otyp == CANDELABRUM_OF_INVOCATION\
				|| (otmp)->otyp == TALLOW_CANDLE\
				|| (otmp)->otyp == WAX_CANDLE\
				|| (otmp)->otyp == JAPAN_WAX_CANDLE\
				|| (otmp)->otyp == OIL_CANDLE\
				|| (otmp)->otyp == GENERAL_CANDLE\
				|| (otmp)->otyp == NATURAL_CANDLE\
				|| (otmp)->otyp == UNSPECIFIED_CANDLE\
				|| (otmp)->otyp == UNAFFECTED_CANDLE\
				|| (otmp)->otyp == SPECIFIC_CANDLE\
				|| (otmp)->otyp == __CANDLE\
				|| (otmp)->otyp == POT_OIL)
/* object can be ignited */
#define ignitable(otmp)	((otmp)->otyp == BRASS_LANTERN\
				|| (otmp)->otyp == OIL_LAMP\
				|| (otmp)->otyp == TORCH\
				|| (otmp)->otyp == CANDELABRUM_OF_INVOCATION\
				|| (otmp)->otyp == TALLOW_CANDLE\
				|| (otmp)->otyp == WAX_CANDLE\
				|| (otmp)->otyp == JAPAN_WAX_CANDLE\
				|| (otmp)->otyp == OIL_CANDLE\
				|| (otmp)->otyp == GENERAL_CANDLE\
				|| (otmp)->otyp == NATURAL_CANDLE\
				|| (otmp)->otyp == UNSPECIFIED_CANDLE\
				|| (otmp)->otyp == UNAFFECTED_CANDLE\
				|| (otmp)->otyp == SPECIFIC_CANDLE\
				|| (otmp)->otyp == __CANDLE\
				|| (otmp)->otyp == MAGIC_CANDLE\
				|| (otmp)->otyp == POT_OIL)

/* footwear counts as high heels */
#define ishighheeled(otmp) ((otmp)->otyp == WEDGE_SANDALS || (otmp)->otyp == FEMININE_PUMPS || (otmp)->otyp == LEATHER_PEEP_TOES || (otmp)->otyp == HIPPIE_HEELS || (otmp)->otyp == PET_STOMPING_PLATFORM_BOOTS || (otmp)->otyp == SENTIENT_HIGH_HEELED_SHOES || (otmp)->otyp == ATSUZOKO_BOOTS || (otmp)->otyp == COMBAT_STILETTOS || (otmp)->otyp == HIGH_STILETTOS || (otmp)->otyp == HIGH_HEELED_SKIERS || (otmp)->otyp == UNFAIR_STILETTOS || (otmp)->otyp == COVETED_BOOTS || (otmp)->otyp == SKY_HIGH_HEELS || (otmp)->otyp == RED_SPELL_HEELS || (otmp)->otyp == DESTRUCTIVE_HEELS || (otmp)->otyp == SINFUL_HEELS || (otmp)->otyp == KILLER_HEELS || (otmp)->otyp == HIGH_SCORING_HEELS || (OBJ_DESCR(objects[otmp->otyp]) && ( (!strcmp(OBJ_DESCR(objects[otmp->otyp]), "irregular boots") || !strcmp(OBJ_DESCR(objects[otmp->otyp]), "neregulyarnyye sapogi") || !strcmp(OBJ_DESCR(objects[otmp->otyp]), "tartibsizlik chizilmasin") || !strcmp(OBJ_DESCR(objects[otmp->otyp]), "wedge boots") || !strcmp(OBJ_DESCR(objects[otmp->otyp]), "klin sapogi") || !strcmp(OBJ_DESCR(objects[otmp->otyp]), "xanjar chizilmasin") || !strcmp(OBJ_DESCR(objects[otmp->otyp]), "winter stilettos") || !strcmp(OBJ_DESCR(objects[otmp->otyp]), "zima stilety") || !strcmp(OBJ_DESCR(objects[otmp->otyp]), "qish sandal chizilmasin") || !strcmp(OBJ_DESCR(objects[otmp->otyp]), "clunky heels") || !strcmp(OBJ_DESCR(objects[otmp->otyp]), "neuklyuzhiye kabluki") || !strcmp(OBJ_DESCR(objects[otmp->otyp]), "qisqa ko'chirish to'piqlarni") || !strcmp(OBJ_DESCR(objects[otmp->otyp]), "ankle boots") || !strcmp(OBJ_DESCR(objects[otmp->otyp]), "botil'ony") || !strcmp(OBJ_DESCR(objects[otmp->otyp]), "bilagi zo'r chizilmasin") || !strcmp(OBJ_DESCR(objects[otmp->otyp]), "block-heeled boots") || !strcmp(OBJ_DESCR(objects[otmp->otyp]), "blok kablukakh sapogi") || !strcmp(OBJ_DESCR(objects[otmp->otyp]), "blok-o'tish chizilmasin") || !strcmp(OBJ_DESCR(objects[otmp->otyp]), "beautiful heels") || !strcmp(OBJ_DESCR(objects[otmp->otyp]), "krasivyye kabluki") || !strcmp(OBJ_DESCR(objects[otmp->otyp]), "chiroyli ko'chirish to'piqlarni") || !strcmp(OBJ_DESCR(objects[otmp->otyp]), "erotic boots") || !strcmp(OBJ_DESCR(objects[otmp->otyp]), "eroticheskiye sapogi") || !strcmp(OBJ_DESCR(objects[otmp->otyp]), "erotik chizilmasin") || !strcmp(OBJ_DESCR(objects[otmp->otyp]), "sputa boots") || !strcmp(OBJ_DESCR(objects[otmp->otyp]), "mokrota sapogi") || !strcmp(OBJ_DESCR(objects[otmp->otyp]), "sputa chizilmasin") || !strcmp(OBJ_DESCR(objects[otmp->otyp]), "femmy boots") || !strcmp(OBJ_DESCR(objects[otmp->otyp]), "zhenskiye sapogi") || !strcmp(OBJ_DESCR(objects[otmp->otyp]), "nazokat etigi") || !strcmp(OBJ_DESCR(objects[otmp->otyp]), "sharp-edged sandals") || !strcmp(OBJ_DESCR(objects[otmp->otyp]), "ostrokonechnyye sandalii") || !strcmp(OBJ_DESCR(objects[otmp->otyp]), "o'tkir xanjarday kavushlari") || !strcmp(OBJ_DESCR(objects[otmp->otyp]), "ski heels") || !strcmp(OBJ_DESCR(objects[otmp->otyp]), "lyzhnyye kabluki") || !strcmp(OBJ_DESCR(objects[otmp->otyp]), "chang'i poshnalar") || !strcmp(OBJ_DESCR(objects[otmp->otyp]), "fetish heels") || !strcmp(OBJ_DESCR(objects[otmp->otyp]), "idol kabluki") || !strcmp(OBJ_DESCR(objects[otmp->otyp]), "but poshnalar") || !strcmp(OBJ_DESCR(objects[otmp->otyp]), "velvet pumps") || !strcmp(OBJ_DESCR(objects[otmp->otyp]), "barkhatnyye nasosy") || !strcmp(OBJ_DESCR(objects[otmp->otyp]), "duxoba nasoslar") || !strcmp(OBJ_DESCR(objects[otmp->otyp]), "buffalo boots") || !strcmp(OBJ_DESCR(objects[otmp->otyp]), "buyvolovyye sapogi") || !strcmp(OBJ_DESCR(objects[otmp->otyp]), "qo'tos botlarni") || !strcmp(OBJ_DESCR(objects[otmp->otyp]), "lolita boots") || !strcmp(OBJ_DESCR(objects[otmp->otyp]), "botinki s lolitoy") || !strcmp(OBJ_DESCR(objects[otmp->otyp]), "bosh ketish etigi") || !strcmp(OBJ_DESCR(objects[otmp->otyp]), "weapon light boots") || !strcmp(OBJ_DESCR(objects[otmp->otyp]), "legkiye botinki dlya oruzhiya") || !strcmp(OBJ_DESCR(objects[otmp->otyp]), "qurol engil etigi") || !strcmp(OBJ_DESCR(objects[otmp->otyp]), "radiant heels") || !strcmp(OBJ_DESCR(objects[otmp->otyp]), "izluchayushchiye kabluki") || !strcmp(OBJ_DESCR(objects[otmp->otyp]), "yorqin ko'chirish to'piqlarni") || !strcmp(OBJ_DESCR(objects[otmp->otyp]), "sexy heels") || !strcmp(OBJ_DESCR(objects[otmp->otyp]), "seksual'nyye kabluki") || !strcmp(OBJ_DESCR(objects[otmp->otyp]), "belgila sexy ko'chirish to'piqlarni") || !strcmp(OBJ_DESCR(objects[otmp->otyp]), "stroking boots") || !strcmp(OBJ_DESCR(objects[otmp->otyp]), "poglazhivaya sapogi") || !strcmp(OBJ_DESCR(objects[otmp->otyp]), "etiklar silay") ) ) ) )

#define ishighheeledb(number) (number == WEDGE_SANDALS || number == FEMININE_PUMPS || number == LEATHER_PEEP_TOES || number == HIPPIE_HEELS || number == PET_STOMPING_PLATFORM_BOOTS || number == SENTIENT_HIGH_HEELED_SHOES || number == ATSUZOKO_BOOTS || number == COMBAT_STILETTOS || number == HIGH_STILETTOS || number == HIGH_HEELED_SKIERS || number == UNFAIR_STILETTOS || number == COVETED_BOOTS || number == SKY_HIGH_HEELS || number == RED_SPELL_HEELS || number == DESTRUCTIVE_HEELS || number == SINFUL_HEELS || number == KILLER_HEELS || number == HIGH_SCORING_HEELS || (OBJ_DESCR(objects[number]) && ( (!strcmp(OBJ_DESCR(objects[number]), "irregular boots") || !strcmp(OBJ_DESCR(objects[number]), "neregulyarnyye sapogi") || !strcmp(OBJ_DESCR(objects[number]), "tartibsizlik chizilmasin") || !strcmp(OBJ_DESCR(objects[number]), "wedge boots") || !strcmp(OBJ_DESCR(objects[number]), "klin sapogi") || !strcmp(OBJ_DESCR(objects[number]), "xanjar chizilmasin") || !strcmp(OBJ_DESCR(objects[number]), "winter stilettos") || !strcmp(OBJ_DESCR(objects[number]), "zima stilety") || !strcmp(OBJ_DESCR(objects[number]), "qish sandal chizilmasin") || !strcmp(OBJ_DESCR(objects[number]), "clunky heels") || !strcmp(OBJ_DESCR(objects[number]), "neuklyuzhiye kabluki") || !strcmp(OBJ_DESCR(objects[number]), "qisqa ko'chirish to'piqlarni") || !strcmp(OBJ_DESCR(objects[number]), "ankle boots") || !strcmp(OBJ_DESCR(objects[number]), "botil'ony") || !strcmp(OBJ_DESCR(objects[number]), "bilagi zo'r chizilmasin") || !strcmp(OBJ_DESCR(objects[number]), "block-heeled boots") || !strcmp(OBJ_DESCR(objects[number]), "blok kablukakh sapogi") || !strcmp(OBJ_DESCR(objects[number]), "blok-o'tish chizilmasin") || !strcmp(OBJ_DESCR(objects[number]), "beautiful heels") || !strcmp(OBJ_DESCR(objects[number]), "krasivyye kabluki") || !strcmp(OBJ_DESCR(objects[number]), "chiroyli ko'chirish to'piqlarni") || !strcmp(OBJ_DESCR(objects[number]), "erotic boots") || !strcmp(OBJ_DESCR(objects[number]), "eroticheskiye sapogi") || !strcmp(OBJ_DESCR(objects[number]), "erotik chizilmasin") || !strcmp(OBJ_DESCR(objects[number]), "sputa boots") || !strcmp(OBJ_DESCR(objects[number]), "mokrota sapogi") || !strcmp(OBJ_DESCR(objects[number]), "sputa chizilmasin") || !strcmp(OBJ_DESCR(objects[number]), "femmy boots") || !strcmp(OBJ_DESCR(objects[number]), "zhenskiye sapogi") || !strcmp(OBJ_DESCR(objects[number]), "nazokat etigi") || !strcmp(OBJ_DESCR(objects[number]), "sharp-edged sandals") || !strcmp(OBJ_DESCR(objects[number]), "ostrokonechnyye sandalii") || !strcmp(OBJ_DESCR(objects[number]), "o'tkir xanjarday kavushlari") || !strcmp(OBJ_DESCR(objects[number]), "ski heels") || !strcmp(OBJ_DESCR(objects[number]), "lyzhnyye kabluki") || !strcmp(OBJ_DESCR(objects[number]), "chang'i poshnalar") || !strcmp(OBJ_DESCR(objects[number]), "fetish heels") || !strcmp(OBJ_DESCR(objects[number]), "idol kabluki") || !strcmp(OBJ_DESCR(objects[number]), "but poshnalar") || !strcmp(OBJ_DESCR(objects[number]), "velvet pumps") || !strcmp(OBJ_DESCR(objects[number]), "barkhatnyye nasosy") || !strcmp(OBJ_DESCR(objects[number]), "duxoba nasoslar") || !strcmp(OBJ_DESCR(objects[number]), "buffalo boots") || !strcmp(OBJ_DESCR(objects[number]), "buyvolovyye sapogi") || !strcmp(OBJ_DESCR(objects[number]), "qo'tos botlarni") || !strcmp(OBJ_DESCR(objects[number]), "lolita boots") || !strcmp(OBJ_DESCR(objects[number]), "botinki s lolitoy") || !strcmp(OBJ_DESCR(objects[number]), "bosh ketish etigi") || !strcmp(OBJ_DESCR(objects[number]), "weapon light boots") || !strcmp(OBJ_DESCR(objects[number]), "legkiye botinki dlya oruzhiya") || !strcmp(OBJ_DESCR(objects[number]), "qurol engil etigi") || !strcmp(OBJ_DESCR(objects[number]), "radiant heels") || !strcmp(OBJ_DESCR(objects[number]), "izluchayushchiye kabluki") || !strcmp(OBJ_DESCR(objects[number]), "yorqin ko'chirish to'piqlarni") || !strcmp(OBJ_DESCR(objects[number]), "sexy heels") || !strcmp(OBJ_DESCR(objects[number]), "seksual'nyye kabluki") || !strcmp(OBJ_DESCR(objects[number]), "belgila sexy ko'chirish to'piqlarni") || !strcmp(OBJ_DESCR(objects[number]), "stroking boots") || !strcmp(OBJ_DESCR(objects[number]), "poglazhivaya sapogi") || !strcmp(OBJ_DESCR(objects[number]), "etiklar silay") ) ) ) )
/* yeah I know, my macros are butt ugly... --Amy */

/* special stones */
#define is_nastygraystone(obj)	( ((obj)->otyp >= RIGHT_MOUSE_BUTTON_STONE) && ((obj)->otyp <= NASTY_STONE) )

#define is_graystone(obj)	((obj)->otyp == LUCKSTONE || \
				 (obj)->otyp == LOADSTONE || \
				 (obj)->otyp == FLINT     || \
				 (obj)->otyp == TALC     || \
				 (obj)->otyp == GRAPHITE     || \
				 (obj)->otyp == VOLCANIC_GLASS_FRAGMENT     || \
				 (obj)->otyp == TOUCHSTONE || \
				 (obj)->otyp == HEALTHSTONE || \
				 (obj)->otyp == SALT_CHUNK || \
				 (obj)->otyp == MANASTONE || \
				 (obj)->otyp == SMALL_PIECE_OF_UNREFINED_MITHR || \
				 (obj)->otyp == SILVER_SLINGSTONE || \
				 (obj)->otyp == STONE_OF_MAGIC_RESISTANCE || \
				 (obj)->otyp == LOADBOULDER || \
				 (obj)->otyp == STARLIGHTSTONE || \
				 (obj)->otyp == SLEEPSTONE || \
				 (obj)->otyp == WHETSTONE || is_nastygraystone(obj) )


/* misc */
#define is_flimsy(otmp)		(objects[(otmp)->otyp].oc_material <= LEATHER || objects[(otmp)->otyp].oc_material == INKA || objects[(otmp)->otyp].oc_material == SILK || \
				 (otmp)->otyp == RUBBER_HOSE)
/* note by Amy: it is intentional that secree and compost don't appear here */

/* helpers, simple enough to be macros */
#define is_plural(o)	((o)->quan > 1 || \
			 (o)->oartifact == ART_EYES_OF_THE_OVERWORLD)

/* Flags for get_obj_location(). */
#define CONTAINED_TOO	0x1
#define BURIED_TOO	0x2

#endif /* OBJ_H */
