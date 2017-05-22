CREATE DATABASE IF NOT EXISTS sistema_riego;

USE sistema_riego;

CREATE USER IF NOT EXISTS 'UsuarioRiego'@'localhost' IDENTIFIED BY 'UsuarioRiego';

GRANT ALL ON sistema_riego.* TO 'UsuarioRiego'@'localhost';

FLUSH PRIVILEGES;

USE sistema_riego;

-- TABLAS.
CREATE TABLE IF NOT EXISTS dato
(
	LuzArduino float NOT NULL
	, LuzReal float NULL
	, TemperaturaArduino float NOT NULL
	, TemperaturaReal float NULL
	, PhArduino float NOT NULL
	, PhReal float NULL
	, HumedadArduino float NOT NULL
	, HumedadReal float NULL
	, Actualizacion datetime NULL
);

-- Agregar valor por defecto a fechatiempo de actualizacion.
ALTER TABLE dato
CHANGE COLUMN Actualizacion Actualizacion datetime NOT NULL
DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP;

-- PROCEDIMIENTOS.
DROP PROCEDURE IF EXISTS ActualizarValores;

-- Actualizar los valores existentes provenientes del arduino.
DELIMITER $$
CREATE PROCEDURE ActualizarValores (IN luz float, IN temperatura float
	, IN ph float, IN humedad float
)
BEGIN
	-- Si no hay registros de valores guardados, insertar uno nuevo.
	IF ((SELECT COUNT(*) FROM dato LIMIT 1) >= 1)
		THEN BEGIN
		UPDATE dato
		SET LuzArduino = luz, TemperaturaArduino = temperatura
		, PhArduino = ph, HumedadArduino = humedad
		, Actualizacion = CURRENT_TIMESTAMP;
END;
	ELSE BEGIN
		INSERT INTO dato(LuzArduino, LuzReal
			, TemperaturaArduino, TemperaturaReal
			, PhArduino, PhReal
			, HumedadArduino, HumedadReal)
		VALUES(luz, 0, temperatura, 0, ph, 0, humedad, 0);
END;
END IF;
END $$
DELIMITER ;

DROP PROCEDURE IF EXISTS ObtenerValoresArduino;

-- Obtener los valores que retorno el Arduino.
DELIMITER $$
CREATE PROCEDURE ObtenerValoresArduino
BEGIN
	SELECT d.LuzArduino, d.TemperaturaArduino, d.PhArduino, d.HumedadArduino
	FROM dato AS d LIMIT 1;
END $$
DELIMITER ;
