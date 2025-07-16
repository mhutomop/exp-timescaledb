CREATE TABLE "movement_history" (
    time timestamp with time zone default now()    not null,
    simulator_id integer                           not null,
    session_id integer                             not null,
    object_id integer                              not null,
    latitude_bearing   double precision            not null,
    longitude_range   double precision             not null
) WITH (
    tsdb.hypertable,
    tsdb.partition_column='time',
    tsdb.segmentby = 'object_id',
    tsdb.orderby = 'time DESC'
);

CREATE TABLE "simulators" (
    id SERIAL PRIMARY KEY,
    name VARCHAR(50) NOT NULL UNIQUE
);

ALTER TABLE "movement_history"
ADD CONSTRAINT fk_simulator_id
FOREIGN KEY (simulator_id)
REFERENCES simulators(id);

INSERT INTO "simulators" (id, name) VALUES (1, 'OSTK-sim'), (2, 'OS-attitude-sim'), (3, 'EO-Sim'), (1000, 'Radar-Sim');

--  Get session by date
SELECT 
    DATE(time) AS date_only,
    session_id,
    MIN(time) AS start_time,
    MAX(time) AS end_time
FROM
    movement_history
WHERE
    DATE(time) = '2025-07-15'
GROUP BY
    DATE(time), session_id;

--  Get object ID by date and session
SELECT object_id FROM movement_history WHERE session_id = 2 GROUP BY object_id;

-- Get movement history data by date, session, object ID, and start-end time
SELECT
    mh.time,
    mh.simulator_id,
    s.name AS simulator_name,
    mh.object_id,
    mh.latitude_bearing,
    mh.longitude_range
FROM
    movement_history AS mh
JOIN
    simulators AS s
ON
    mh.simulator_id = s.id
WHERE
    mh.object_id = 0
    AND mh.session_id = 0
    AND mh.time BETWEEN '2025-07-15 08:29:00+07' AND '2025-07-15 11:45:00+07'
ORDER BY
    mh.simulator_id;
