import React from 'react'

const Card = () => {
  return (
    < div className="bg-blue-100 shadow-md rounded-lg p-2 flex flex-col items-center" >
      <h3 className="text-sm font-semibold">Temperature</h3>
      {/* Placeholder for Graph */}
      <div className="h-20 w-[135px] bg-gray-100 mt-2 rounded-sm">
        <iframe
          width="450"
          height="260"
          style={{ transform: "scale(0.3)", transformOrigin: "top left", border: "1px solid #cccccc" }} // Corrected style syntax
          src="https://thingspeak.com/channels/2653582/charts/1?bgcolor=%23ffffff&color=%23d62020&dynamic=true&results=60&type=line&update=15"
        ></iframe>
      </div>
    </div >
  )
}

export default Card
