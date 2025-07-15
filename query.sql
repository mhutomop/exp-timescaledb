
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

--  Get session by date
SELECT DATE(time), session_id,
    MIN(strftime('%H:%M:%f', time)) as start_time,
    MAX(strftime('%H:%M:%f', time)) as end_time 
FROM movement_history 
WHERE DATE(time)='2025-06-25' GROUP BY session_id;

--  Get object ID by date and session
SELECT object_id FROM movement_history WHERE session_id = 2 GROUP BY object_id;

-- Get movement history data by date, session, object ID, and start-end time
SELECT  time, simulator_id, object_id, latitude_bearing , longitude_range  
FROM object_movement_history 
WHERE object_id = 2 and session_id = 2 
	and strftime('%H:%M:%f', time) BETWEEN '08:29:00' and '08:45:00'
ORDER BY simulator_id;