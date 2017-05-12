function Indicador(nombre, colorFondo, colorTexto, valor) {
	this.nombre = String(nombre);
	this.colorFondo = String(colorFondo);
	this.colorTexto = String(colorTexto);
	this.valor = Number(valor);
}

let indicador = [
	Indicador("Luz", "orange", "white", 0),
	Indicador("Temperatura", "red", "white", 0),
	Indicador("pH", "blue", "white", 0),
	Indicador("Humedad", "grey darken-1", "white", 0)
];

function ObtenerHtmlIndicadores(indicadores) {
	// Html a retornar.
	var html = "";

	for(

	return html;
};

$(document).ready(function() {
});	
