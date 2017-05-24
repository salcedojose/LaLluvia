<?php
// CONSTANTES.
// Ruta del archivo que contiene la conexion.
define("RUTA_CONEXION", "Conn.php");
// Nombre de procedimiento con el cual obtener valores.
define("PROCEDIMIENTO_OBTENER_VALORES_ARDUINO", "ObtenerValoresArduino");
// Valores dentro de un registro a obtener.
define("LUZ", "LuzArduino");
define("TEMPERATURA", "TemperaturaArduino");
define("PH", "PhArduino");
define("HUMEDAD", "HumedadArduino");
define("REGANDO", "Regando");

include_once RUTA_CONEXION;

// Preparacion de llamada al procedimiento almacenado.
$Procedimiento = $con->prepare("CALL " . PROCEDIMIENTO_OBTENER_VALORES_ARDUINO);

// Ejecutar la consulta.
if ($Procedimiento->execute()) {
	// Valores a retornar por JSON.
	$valoresJson = array();

	// Obtener los valores obtenidos de almacenamiento.
	$registro = $Procedimiento->fetch(PDO::FETCH_ASSOC);

	// Guardar los valores obtenidos en formato Json.
	$valoresJson[] = array(
		LUZ => $registro[LUZ]
		, TEMPERATURA => $registro[TEMPERATURA]
		, PH => $registro[PH]
		, HUMEDAD => $registro[HUMEDAD]
		, REGANDO => $registro[REGANDO]
	);

	// Encodificar los datos de vuelta en forma de JSON.
	echo json_encode($valoresJson);
} else {
	echo "Falla de conexion.";
}
?>
