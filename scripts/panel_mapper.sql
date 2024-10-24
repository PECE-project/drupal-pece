-- Add a new field & populate it
ALTER TABLE `panels_pane` ADD COLUMN `linked_uuid` char(36);
UPDATE `panels_pane` SET `linked_uuid` = substring(`subtype`, 7) WHERE `subtype` LIKE 'vuuid:%';
UPDATE `panels_pane` SET `linked_uuid` = substring(`subtype`, 6) WHERE `subtype` LIKE 'uuid:%';
-- Index the field and the UUID in panel revision (to the insert won't take hours)
ALTER TABLE `panels_pane` ADD INDEX `ix_pp_linked_uuid` (`did`, `linked_uuid`);
ALTER TABLE `fieldable_panels_panes_revision` ADD INDEX `ix_fppr_vuuid` (`vuuid`);
-- Create our results mapping table
CREATE OR REPLACE TABLE `panel_map` (
    `did` int(11) DEFAULT NULL,
    `uuid` char(36) DEFAULT NULL,
    `entity_id` int(11) DEFAULT NULL,
    `bundle` varchar(255) DEFAULT NULL
);
-- Populate the mapping table
INSERT INTO `panel_map` (did, uuid, entity_id, bundle)
SELECT pp.did, pp.linked_uuid, fpr.fpid as entity_id, fpp.bundle
FROM panels_pane pp
INNER JOIN fieldable_panels_panes_revision fpr ON pp.linked_uuid = fpr.vuuid
INNER JOIN fieldable_panels_panes fpp ON fpr.fpid = fpp.fpid;
-- Make sure the map is unique, and provide an index
ALTER TABLE `panel_map` ADD PRIMARY KEY (did, entity_id);
