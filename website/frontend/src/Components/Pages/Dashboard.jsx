import Card from "../NotPages/Card";


function Dashboard() {
  return (
    <div className="min-h-screen bg-bluePrime p-4 flex flex-col items-center text-gray-800">

      {/* Header Section */}
      <div className="flex justify-between w-full items-center mb-4">
        <div className="flex items-center space-x-2">
          <span className="text-xl">📍</span>
          <h1 className="text-l font-semibold">Bangalore, Karnataka</h1>
        </div>
        <p className="text-xxs text-gray-600">Time since update: &lt;time&gt;</p>
      </div>

      {/* Circular Gauge */}
      <div className="flex justify-center items-center mb-6">
        <div className="relative flex w-[100px]">
          <svg width="100" height="50" className="absolute top-0 left-0">
            {/* Background Arc */}
            <path
              d="M10,50 A40,40 0 0,1 90,50"
              fill="none"
              stroke="#e0e7ff"
              strokeWidth="10"
            />
            {/* Progress Arc */}
            <path
              d="M10,50 A40,40 0 0,1 70,15" // Adjust this path for dynamic data
              fill="none"
              stroke="#60a5fa"
              strokeWidth="10"
            />
          </svg>
          <div className="text-blue-600 text-4xl font-bold mt-4 m-auto">75</div>
        </div>
      </div>

      {/* Weather Report */}
      <div className="bg-blue-100 shadow-md rounded-lg p-4 w-full max-w-md mb-6">
        <h2 className="text-center font-semibold text-gray-700">Weather Report</h2>
        {/* Placeholder for Weather Data */}
      </div>

      {/* Data Cards */}
      <div className="grid grid-cols-2 gap-4 w-full max-w-md">
        {/* Temperature Card */}
        <Card name="Temperature" myframe="https://thingspeak.com/channels/2653582/charts/1?bgcolor=%23ffffff&color=%23d62020&dynamic=true&results=60&type=line&update=15" />
        <Card name="Humidity" myframe="https://thingspeak.com/channels/2653582/charts/2?bgcolor=%23ffffff&color=%23d62020&dynamic=true&results=60&type=line&update=15" />
        <Card name="Dust" myframe="https://thingspeak.com/channels/2653582/charts/3?bgcolor=%23ffffff&color=%23d62020&dynamic=true&results=60&type=line&update=15" />
        <Card name="Qzone" myframe="https://thingspeak.com/channels/2653582/charts/4?bgcolor=%23ffffff&color=%23d62020&dynamic=true&results=60&type=line&update=15" />
        <Card name="Gases Quality" myframe="https://thingspeak.com/channels/2653582/charts/5?bgcolor=%23ffffff&color=%23d62020&dynamic=true&results=60&type=line&update=15" />

      </div>
    </div >
  );
}

export default Dashboard;
