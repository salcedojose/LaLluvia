// FUNCIONES.
// Desplegar el valor en un elemento grafico.
function DesplegarValor(elementoId, valor)
{
	$(elementoId).html(valor);
}

function DesplegarValoresArduino(luzId, temperaturaId, phId, humedadId, regandoId)
{
	// Llamada ajax para obtener valores obtenidos de Arduino.
	$.ajax({
		type: "GET",
		url: "script/data/ObtenerValoresArduino.php",
		success: function (jsonData) {
			// Procesar valores encodificados en json.
			const valoresArduino = JSON.parse(jsonData);

			// Desplegar los valores en los elementos apropiados.
			DesplegarValor(luzId, valoresArduino[0].LuzArduino);
			DesplegarValor(temperaturaId, valoresArduino[0].TemperaturaArduino);
			DesplegarValor(phId, valoresArduino[0].PhArduino);
			DesplegarValor(humedadId, valoresArduino[0].HumedadArduino);

			// Definir si mostrar si esta regando o no.
			let regando = "";
			if (valoresArduino[0].Regando >= 1) {
				regando = "Regando.";
			} else {
				regando = "Parado.";
			}
			DesplegarValor(regandoId, regando);
		}, error: function(data) {
			alert(data.d);
		}
	});
}

// CONSTANTES.
// Tiempo para actualizar los valores de arduino.
const ESPERA_MILISEGUNDOS = 5000;
// Identificadores de elementos que contendran los valores deseados.
const LUZ_ID = "#Luz";
const TEMPERATURA_ID = "#Temperatura";
const PH_ID = "#Ph";
const HUMEDAD_ID = "#Humedad";
const REGANDO_ID = "#Regando";

// PRINCIPAL.
$(document).ready(function() {
	// Desplegar los valores del arduino al iniciar y cada cierto tiempo.
	DesplegarValoresArduino(LUZ_ID, TEMPERATURA_ID, PH_ID, HUMEDAD_ID, REGANDO_ID);
	setTimeout(function() {
		DesplegarValoresArduino(LUZ_ID, TEMPERATURA_ID, PH_ID, HUMEDAD_ID, REGANDO_ID);
	}, ESPERA_MILISEGUNDOS);
});
