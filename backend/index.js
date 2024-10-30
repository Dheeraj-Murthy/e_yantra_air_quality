const express = require('express');
const cors = require('cors');
const app = express();

app.use(cors()); // Allow CORS requests
app.use(express.json());

const PORT = 5001;

// Simple route
app.get('/', (req, res) => {
  res.json({ message: "Hello from the server!" });
});

app.listen(PORT, () => {
  console.log(`Server running on http://localhost:${PORT}`);
});
