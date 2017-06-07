INSERT INTO `migrations` VALUES ('20170607215004');

-- Scarabs
UPDATE creature_loot_template SET ChanceOrQuestChance=2 WHERE item IN (20858,20859,20860,20861,20862,20863,20864,20865);
UPDATE creature_loot_template SET ChanceOrQuestChance=6 WHERE item IN (20858,20859,20860,20861,20862,20863,20864,20865) AND entry = 15333;
UPDATE creature_loot_template SET ChanceOrQuestChance=4 WHERE item IN (20858,20859,20860,20861,20862,20863,20864,20865) AND entry = 15335;

-- AQ40 Idols
UPDATE creature_loot_template SET ChanceOrQuestChance=0.4 WHERE item IN (20874,20875,20876,20877,20878,20879,20881,20882);

-- Delete from AQ20 mobs
DELETE FROM creature_loot_template WHERE item IN (20874,20875,20876,20877,20878,20879,20881,20882) 
AND entry IN (15318,15319,15320,15323,15324,15325,15327,15333,15335,15336,15338,15343,15344,15355,15386,15387,15392,15461,15462,15505);

-- AQ20 Idols
UPDATE creature_loot_template SET ChanceOrQuestChance=0.4 WHERE item IN (20866,20867,20868,20869,20870,20871,20872,20873);
UPDATE creature_loot_template SET ChanceOrQuestChance=1.3 WHERE item IN (20866,20867,20868,20869,20870,20871,20872,20873) AND entry = 15333;
UPDATE creature_loot_template SET ChanceOrQuestChance=0.6 WHERE item IN (20866,20867,20868,20869,20870,20871,20872,20873) AND entry = 15335;

-- Delete from AQ40 mobs
DELETE FROM creature_loot_template WHERE item IN (20866,20867,20868,20869,20870,20871,20872,20873) 
AND entry IN (15229,15230,15233,15235,15236,15240,15246,15247,15249,15250,15252,15262,15264,15277,15311,15312,15316,15317);

-- Add to AQ20 mobs
DELETE FROM creature_loot_template WHERE item IN (20866,20867,20868,20869,20870,20871,20872,20873) AND entry IN (15343,15386,15392);
INSERT INTO creature_loot_template (entry, item, ChanceOrQuestChance) VALUES 
(15343, 20866, 0.4),
(15343, 20867, 0.4),
(15343, 20868, 0.4),
(15343, 20869, 0.4),
(15343, 20870, 0.4),
(15343, 20871, 0.4),
(15343, 20872, 0.4),
(15343, 20873, 0.4),
(15386, 20866, 0.4),
(15386, 20867, 0.4),
(15386, 20868, 0.4),
(15386, 20869, 0.4),
(15386, 20870, 0.4),
(15386, 20871, 0.4),
(15386, 20872, 0.4),
(15386, 20873, 0.4),
(15392, 20866, 0.4),
(15392, 20867, 0.4),
(15392, 20868, 0.4),
(15392, 20869, 0.4),
(15392, 20870, 0.4),
(15392, 20871, 0.4),
(15392, 20872, 0.4),
(15392, 20873, 0.4);
