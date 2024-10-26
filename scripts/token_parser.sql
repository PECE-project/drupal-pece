CREATE OR REPLACE TABLE fid_locator (id INT NOT NULL, found_in VARCHAR(255), bundle VARCHAR(128) NOT NULL, found_val TEXT, fid INT NULL);

insert into fid_locator (id, bundle, found_in, found_val)
WITH RECURSIVE cte (id, bundle, found_val, remainder, lvl) AS (
SELECT entity_id AS id, bundle, body_value AS found_val, body_value AS remainder, 1 AS lvl
FROM field_data_body
WHERE body_value like '%}]]%'
UNION ALL
SELECT id, bundle,
SUBSTRING(REGEXP_SUBSTR(SUBSTRING_INDEX(remainder, '}]]', 1),'\\[\\[{.*'), 3),
SUBSTR(remainder, INSTR(remainder, '}]]') + 3),
lvl + 1
FROM cte
WHERE remainder like '%}]]%'
)
select id, bundle, 'body' as found_in, found_val
from cte
where lvl > 1;
--body

insert into fid_locator (id, bundle, found_in, found_val)
WITH RECURSIVE cte (id, bundle, found_val, remainder, lvl) AS (
SELECT entity_id AS id, bundle, comment_body_value AS found_val, comment_body_value AS remainder, 1 AS lvl
FROM field_data_comment_body
WHERE comment_body_value like '%}]]%'
UNION ALL
SELECT id, bundle,
SUBSTRING(REGEXP_SUBSTR(SUBSTRING_INDEX(remainder, '}]]', 1),'\\[\\[{.*'), 3),
SUBSTR(remainder, INSTR(remainder, '}]]') + 3),
lvl + 1
FROM cte
WHERE remainder like '%}]]%'
)
select id, bundle, 'comment_body' as found_in, found_val
from cte
where lvl > 1;
--comment_body

insert into fid_locator (id, bundle, found_in, found_val)
WITH RECURSIVE cte (id, bundle, found_val, remainder, lvl) AS (
SELECT entity_id AS id, bundle, field_basic_file_text_value AS found_val, field_basic_file_text_value AS remainder, 1 AS lvl
FROM field_data_field_basic_file_text
WHERE field_basic_file_text_value like '%}]]%'
UNION ALL
SELECT id, bundle,
SUBSTRING(REGEXP_SUBSTR(SUBSTRING_INDEX(remainder, '}]]', 1),'\\[\\[{.*'), 3),
SUBSTR(remainder, INSTR(remainder, '}]]') + 3),
lvl + 1
FROM cte
WHERE remainder like '%}]]%'
)
select id, bundle, 'comment_body' as found_in, found_val
from cte
where lvl > 1;
--field_basic_file_text

insert into fid_locator (id, bundle, found_in, found_val)
WITH RECURSIVE cte (id, bundle, found_val, remainder, lvl) AS (
SELECT entity_id AS id, bundle, field_basic_image_caption_value AS found_val, field_basic_image_caption_value AS remainder, 1 AS lvl
FROM field_data_field_basic_image_caption
WHERE field_basic_image_caption_value like '%}]]%'
UNION ALL
SELECT id, bundle,
SUBSTRING(REGEXP_SUBSTR(SUBSTRING_INDEX(remainder, '}]]', 1),'\\[\\[{.*'), 3),
SUBSTR(remainder, INSTR(remainder, '}]]') + 3),
lvl + 1
FROM cte
WHERE remainder like '%}]]%'
)
select id, bundle, 'field_basic_image_caption' as found_in, found_val
from cte
where lvl > 1;
--field_basic_image_caption

insert into fid_locator (id, bundle, found_in, found_val)
WITH RECURSIVE cte (id, bundle, found_val, remainder, lvl) AS (
SELECT entity_id AS id, bundle, field_basic_text_text_value AS found_val, field_basic_text_text_value AS remainder, 1 AS lvl
FROM field_data_field_basic_text_text
WHERE field_basic_text_text_value like '%}]]%'
UNION ALL
SELECT id, bundle,
SUBSTRING(REGEXP_SUBSTR(SUBSTRING_INDEX(remainder, '}]]', 1),'\\[\\[{.*'), 3),
SUBSTR(remainder, INSTR(remainder, '}]]') + 3),
lvl + 1
FROM cte
WHERE remainder like '%}]]%'
)
select id, bundle, 'field_basic_text_text' as found_in, found_val
from cte
where lvl > 1;
--field_basic_text_text

insert into fid_locator (id, bundle, found_in, found_val)
WITH RECURSIVE cte (id, bundle, found_val, remainder, lvl) AS (
SELECT entity_id AS id, bundle, field_description_value AS found_val, field_description_value AS remainder, 1 AS lvl
FROM field_data_field_description
WHERE field_description_value like '%}]]%'
UNION ALL
SELECT id, bundle,
SUBSTRING(REGEXP_SUBSTR(SUBSTRING_INDEX(remainder, '}]]', 1),'\\[\\[{.*'), 3),
SUBSTR(remainder, INSTR(remainder, '}]]') + 3),
lvl + 1
FROM cte
WHERE remainder like '%}]]%'
)
select id, bundle, 'field_description' as found_in, found_val
from cte
where lvl > 1;
--field_description

insert into fid_locator (id, bundle, found_in, found_val)
WITH RECURSIVE cte (id, bundle, found_val, remainder, lvl) AS (
SELECT entity_id AS id, bundle, field_map_information_value AS found_val, field_map_information_value AS remainder, 1 AS lvl
FROM field_data_field_map_information
WHERE field_map_information_value like '%}]]%'
UNION ALL
SELECT id, bundle,
SUBSTRING(REGEXP_SUBSTR(SUBSTRING_INDEX(remainder, '}]]', 1),'\\[\\[{.*'), 3),
SUBSTR(remainder, INSTR(remainder, '}]]') + 3),
lvl + 1
FROM cte
WHERE remainder like '%}]]%'
)
select id, bundle, 'field_map_information' as found_in, found_val
from cte
where lvl > 1;
--field_map_information

insert into fid_locator (id, bundle, found_in, found_val)
WITH RECURSIVE cte (id, bundle, found_val, remainder, lvl) AS (
SELECT entity_id AS id, bundle, field_pece_application_reason_value AS found_val, field_pece_application_reason_value AS remainder, 1 AS lvl
FROM field_data_field_pece_application_reason
WHERE field_pece_application_reason_value like '%}]]%'
UNION ALL
SELECT id, bundle,
SUBSTRING(REGEXP_SUBSTR(SUBSTRING_INDEX(remainder, '}]]', 1),'\\[\\[{.*'), 3),
SUBSTR(remainder, INSTR(remainder, '}]]') + 3),
lvl + 1
FROM cte
WHERE remainder like '%}]]%'
)
select id, bundle, 'field_pece_application_reason' as found_in, found_val
from cte
where lvl > 1;
--field_pece_application_reason

insert into fid_locator (id, bundle, found_in, found_val)
WITH RECURSIVE cte (id, bundle, found_val, remainder, lvl) AS (
SELECT entity_id AS id, bundle, field_pece_biography_value AS found_val, field_pece_biography_value AS remainder, 1 AS lvl
FROM field_data_field_pece_biography
WHERE field_pece_biography_value like '%}]]%'
UNION ALL
SELECT id, bundle,
SUBSTRING(REGEXP_SUBSTR(SUBSTRING_INDEX(remainder, '}]]', 1),'\\[\\[{.*'), 3),
SUBSTR(remainder, INSTR(remainder, '}]]') + 3),
lvl + 1
FROM cte
WHERE remainder like '%}]]%'
)
select id, bundle, 'field_pece_biography' as found_in, found_val
from cte
where lvl > 1;
--field_pece_biography

insert into fid_locator (id, bundle, found_in, found_val)
WITH RECURSIVE cte (id, bundle, found_val, remainder, lvl) AS (
SELECT entity_id AS id, bundle, field_pece_crit_commentary_value AS found_val, field_pece_crit_commentary_value AS remainder, 1 AS lvl
FROM field_data_field_pece_crit_commentary
WHERE field_pece_crit_commentary_value like '%}]]%'
UNION ALL
SELECT id, bundle,
SUBSTRING(REGEXP_SUBSTR(SUBSTRING_INDEX(remainder, '}]]', 1),'\\[\\[{.*'), 3),
SUBSTR(remainder, INSTR(remainder, '}]]') + 3),
lvl + 1
FROM cte
WHERE remainder like '%}]]%'
)
select id, bundle, 'field_pece_crit_commentary' as found_in, found_val
from cte
where lvl > 1;
--field_pece_crit_commentary

insert into fid_locator (id, bundle, found_in, found_val)
WITH RECURSIVE cte (id, bundle, found_val, remainder, lvl) AS (
SELECT entity_id AS id, bundle, field_pece_proj_notes_value AS found_val, field_pece_proj_notes_value AS remainder, 1 AS lvl
FROM field_data_field_pece_proj_notes
WHERE field_pece_proj_notes_value like '%}]]%'
UNION ALL
SELECT id, bundle,
SUBSTRING(REGEXP_SUBSTR(SUBSTRING_INDEX(remainder, '}]]', 1),'\\[\\[{.*'), 3),
SUBSTR(remainder, INSTR(remainder, '}]]') + 3),
lvl + 1
FROM cte
WHERE remainder like '%}]]%'
)
select id, bundle, 'field_pece_proj_notes' as found_in, found_val
from cte
where lvl > 1;
--field_pece_proj_notes

insert into fid_locator (id, bundle, found_in, found_val)
WITH RECURSIVE cte (id, bundle, found_val, remainder, lvl) AS (
SELECT entity_id AS id, bundle, field_pece_source_value AS found_val, field_pece_source_value AS remainder, 1 AS lvl
FROM field_data_field_pece_source
WHERE field_pece_source_value like '%}]]%'
UNION ALL
SELECT id, bundle,
SUBSTRING(REGEXP_SUBSTR(SUBSTRING_INDEX(remainder, '}]]', 1),'\\[\\[{.*'), 3),
SUBSTR(remainder, INSTR(remainder, '}]]') + 3),
lvl + 1
FROM cte
WHERE remainder like '%}]]%'
)
select id, bundle, 'field_pece_source' as found_in, found_val
from cte
where lvl > 1;
--field_pece_source

insert into fid_locator (id, bundle, found_in, found_val)
WITH RECURSIVE cte (id, bundle, found_val, remainder, lvl) AS (
SELECT entity_id AS id, bundle, field_user_about_value AS found_val, field_user_about_value AS remainder, 1 AS lvl
FROM field_data_field_user_about
WHERE field_user_about_value like '%}]]%'
UNION ALL
SELECT id, bundle,
SUBSTRING(REGEXP_SUBSTR(SUBSTRING_INDEX(remainder, '}]]', 1),'\\[\\[{.*'), 3),
SUBSTR(remainder, INSTR(remainder, '}]]') + 3),
lvl + 1
FROM cte
WHERE remainder like '%}]]%'
)
select id, bundle, 'field_user_about' as found_in, found_val
from cte
where lvl > 1;
--field_user_about

update fid_locator set fid = substring_index(substr(regexp_substr(found_val,'fid":"\\d+"'), 7), '"', 1);
