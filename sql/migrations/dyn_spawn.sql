ALTER TABLE creature ADD spawntimesecsmin INT(10) UNSIGNED DEFAULT 0 NOT NULL COMMENT 'Creature respawn time minimum, 0 not set'
AFTER spawntimesecs;
 
ALTER TABLE creature ADD spawntimesecsmax INT(10) UNSIGNED DEFAULT 0 NOT NULL COMMENT 'Creature respawn time maximum, 0 not set' AFTER spawntimesecsmin;

ALTER TABLE gameobject ADD spawntimesecsmin INT(11) DEFAULT 0 NOT NULL COMMENT 'Gameobject respawn time minimum, 0 not set' AFTER spawntimesecs;
 
ALTER TABLE gameobject ADD spawntimesecsmax INT(11) DEFAULT 0 NOT NULL COMMENT 'Gameobject respawn time maximum, 0 not set' AFTER spawntimesecsmin;
