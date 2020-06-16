namespace cpp Thrift

struct SensorDataMessage {
	1:string newestTempData;
	2:string newestWindData;
	3:string newestHumidityData;
	4:string newestBrightnessData;
}

exception ClientUnavailable {
	1:string message;
}

service SendSensordataService {
	SensorDataMessage getSensorData() throws (1:ClientUnavailable unavailable);
}
