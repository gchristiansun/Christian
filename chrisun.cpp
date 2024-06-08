
#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <chrono>
#include <map>
#include <algorithm>

#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

const string MARK = "🟢]";
const string MARK_WARNING = "⚠️ ]";
const string MARK_OUTPUT = "=| ";
const string MARK_INPUT = "===> ";

const long long unsigned int INFINITY = LONG_LONG_MAX;

// Struct to represent a vertex in a graph
struct Vertex
{
  string name;

  // Constructor Function to initialize the vertex
  Vertex(const string &vertexName) : name(vertexName) {}
};

// Struct to represent an edge in a graph
struct Edge
{
  Vertex *firstVertex;
  Vertex *secondVertex;
  int weight;

  // Constructor Function to initialize the edge
  Edge(Vertex *firstVertex, Vertex *secondVertex, int edgeWeight)
      : firstVertex(firstVertex), secondVertex(secondVertex), weight(edgeWeight) {}
};

// Struct to represent a graph
struct Graph
{
  vector<Vertex *> vertices;
  vector<Edge *> edges;

  // Method/Function to add a vertex to the graph
  void addVertex(Vertex *vertex) { vertices.push_back(vertex); }

  // Method/Function to add an edge to the graph
  void addEdge(Edge *edge) { edges.push_back(edge); }

  // Method/Function to add a non-directional edge to the graph
  bool addNonDirectionalEdge(Vertex *firstVertex, Vertex *secondVertex, int edgeWeight)
  {
    for (Edge *edge : edges)
    {
      if ((edge->firstVertex == firstVertex && edge->secondVertex == secondVertex) || (edge->firstVertex == secondVertex && edge->secondVertex == firstVertex))
      {
        cout << "Edge already exists" << endl;
        return false;
      }
    }
    Edge *firstEdge = new Edge(firstVertex, secondVertex, edgeWeight);
    addEdge(firstEdge);

    return true;
  }

  void reverseEdges()
  {
    for (const auto &edge : edges)
    {
      Vertex *temp = edge->firstVertex;
      edge->firstVertex = edge->secondVertex;
      edge->secondVertex = temp;
    }

    //  Reverse the vector
    reverse(edges.begin(), edges.end());
  }

  // Method/Function to get all the edges of a vertex
  vector<Edge *> getEdges(Vertex *vertex)
  {
    vector<Edge *> vertexEdges;
    for (Edge *edge : edges)
    {
      if (edge->firstVertex == vertex || edge->secondVertex == vertex)
      {
        vertexEdges.push_back(edge);
      }
    }

    for (Edge *edge : vertexEdges)
    {
      // Tukar Vertex: Untuk memastiikan bahwa vertex pertama adalah vertex yang diminta
      if (edge->firstVertex != vertex)
      {
        Vertex *temp = edge->firstVertex;
        edge->firstVertex = edge->secondVertex;
        edge->secondVertex = temp;
      }
    }
    return vertexEdges;
  }
};

// Struct to represent a queue
struct Queue
{
  vector<Graph> graphs;

  // Method/Function to add a graph to the queue
  void addGraph(const Graph &graph) { graphs.push_back(graph); }

  // Method/Function to remove first graph from the queue
  void removeGraph() { graphs.erase(graphs.begin()); }
};

void printBanner();
void println(const string &message, bool is_warning = false);
string inputln(const string &message, bool is_warning = false);
void clearTerminal();
void clearConfirmation();
void delay(int milliseconds);
void setConsoleOutputUTF8();
void generateMainRouteVertices(Graph *mainRoute);
void generateHistory(Queue *fastestRouteHistory, Graph *mainRoute);

// Main Function
void createStation(Graph &mainRoute);
void viewStation(Graph &mainRoute);
void createRoute(Graph &mainRoute);
void findFastestRoute(Graph &mainRoute, Queue &fastestRouteHistory);
void viewFastestRouteHistory(Queue &fastestRouteHistory);
void deleteRoute(Graph &mainRoute);
void deleteStation(Graph &mainRoute);
void exitOutput();

int main(int argc, char const *argv[]) {
    // Set the console output to UTF-8 (For Emoji Support)
    setConsoleOutputUTF8();

    printBanner();

    Graph mainRoute;
    generateMainRouteVertices(&mainRoute);

    Queue fastestRouteHistory;
    generateHistory(&fastestRouteHistory, &mainRoute);

    do {
        clearTerminal();

        println("Manajemen KRL");
        println("1. Tambah Stasiun");
        println("2. Lihat Stasiun");
        println("3. Tambah Rute");
        println("4. Cari Rute Tercepat");
        println("5. Lihat histori rute tercepat");
        println("6. Hapus Rute");
        println("7. Hapus Stasiun");
        println("8. Keluar\n");

        // Get user input
        string input = inputln("Pilih menu: ");

        // Validate user input
        if (input.find_first_not_of("12345678") != string::npos || input.empty()) {
            input = "0";
        }

        // Handle user input
        switch (stoi(input)) {
            case 1:
                createStation(mainRoute);
                continue;
            case 2:
                viewStation(mainRoute);
                continue;
            case 3:
                createRoute(mainRoute);
                continue;
            case 4:
                findFastestRoute(mainRoute, fastestRouteHistory);
                continue;
            case 5:
                viewFastestRouteHistory(fastestRouteHistory);
                continue;
            case 6:
                deleteRoute(mainRoute);
                continue;
            case 7:
                deleteStation(mainRoute);
                continue;
            case 8:
                exitOutput();
                return 0;
            default:
                println("Menu tidak valid! (pilih angka 1-8)", true);
                delay(2056);
                continue;
        }

    } while (true);

    return 0;
}

void printBanner()
{
  clearTerminal();
  cout << "\033[2J\033[1;1H";
    cout << "=======================\n";
    cout << "     Rute Tercepat     \n";
    cout << "=======================\n\n";
}

// Function to print a normal message to the console
void println(const string &message, bool is_warning)
{
  if (is_warning)
  {
    cout << MARK_WARNING << MARK_OUTPUT << message << endl;
    return;
  }

  cout << MARK << MARK_OUTPUT << message << endl;
}

// Function to print a message with input prompt to the console
string inputln(const string &message, bool is_warning)
{
  if (is_warning)
  {
    cout << MARK_WARNING << MARK_INPUT << message;
  }
  else
  {
    cout << MARK << MARK_INPUT << message;
  }

  string input;
  getline(cin, input);

  return input;
}

// Function to clear the terminal
void clearTerminal()
{
  system("cls||clear");
  cout << "\033[2J\033[1;1H";
    cout << "=======================\n";
    cout << "     Rute Tercepat     \n";
    cout << "=======================\n\n";
}

// Function to clear the confirmation message
void clearConfirmation()
{
  inputln("Tekan enter untuk melanjutkan...");
  clearTerminal();
}

void setConsoleOutputUTF8()
{
#ifdef _WIN32
  SetConsoleOutputCP(CP_UTF8);
#endif
}

void delay(int milliseconds)
{
  this_thread::sleep_for(chrono::milliseconds(milliseconds));
}

void generateMainRouteVertices(Graph *mainRoute)
{
  Vertex *sukasari = new Vertex("Sukasari");
  Vertex *cimenyan = new Vertex("Cimenyan");
  Vertex *cicendo = new Vertex("Cicendo");
  Vertex *cibiru = new Vertex("Cibiru");
  Vertex *ujungBerung = new Vertex("Ujung Berung");
  Vertex *cicaheum = new Vertex("Cicaheum");
  Vertex *astanaAnyar = new Vertex("Astana Anyar");
  Vertex *cimahi = new Vertex("Cimahi");
  Vertex *lembang = new Vertex("Lembang");
  Vertex *cihampelas = new Vertex("Cihampelas");
  Vertex *cisarua = new Vertex("Cisarua");

  mainRoute->addVertex(sukasari);
  mainRoute->addVertex(cimenyan);
  mainRoute->addVertex(cicendo);
  mainRoute->addVertex(cibiru);
  mainRoute->addVertex(ujungBerung);
  mainRoute->addVertex(cicaheum);
  mainRoute->addVertex(astanaAnyar);
  mainRoute->addVertex(cimahi);
  mainRoute->addVertex(lembang);
  mainRoute->addVertex(cihampelas);
  mainRoute->addVertex(cisarua);

  mainRoute->addNonDirectionalEdge(sukasari, cisarua, 4);
  mainRoute->addNonDirectionalEdge(sukasari, cimenyan, 7);
  mainRoute->addNonDirectionalEdge(sukasari, lembang, 5);
  mainRoute->addNonDirectionalEdge(sukasari, cicendo, 7);

  mainRoute->addNonDirectionalEdge(cicendo, cicaheum, 5);
  mainRoute->addNonDirectionalEdge(cicendo, cimahi, 8);
  mainRoute->addNonDirectionalEdge(cicendo, astanaAnyar, 3);

  mainRoute->addNonDirectionalEdge(cimenyan, cicaheum, 8);
  mainRoute->addNonDirectionalEdge(cimenyan, lembang, 4);

  mainRoute->addNonDirectionalEdge(cibiru, ujungBerung, 3);
  mainRoute->addNonDirectionalEdge(cibiru, astanaAnyar, 9);
  mainRoute->addNonDirectionalEdge(ujungBerung, cicaheum, 5);

  mainRoute->addNonDirectionalEdge(cicaheum, astanaAnyar, 7);
  mainRoute->addNonDirectionalEdge(astanaAnyar, cimahi, 10);
  mainRoute->addNonDirectionalEdge(astanaAnyar, cihampelas, 14);

  mainRoute->addNonDirectionalEdge(cimahi, cihampelas, 7);
  mainRoute->addNonDirectionalEdge(cimahi, cisarua, 8);
  mainRoute->addNonDirectionalEdge(lembang, cisarua, 6);
}

void generateHistory(Queue *fastestRouteHistory, Graph *mainRoute)
{
  Graph route1;

  route1.addVertex(mainRoute->vertices[0]);
  route1.addVertex(mainRoute->vertices[1]);
  route1.addVertex(mainRoute->vertices[5]);

  route1.addNonDirectionalEdge(mainRoute->vertices[0], mainRoute->vertices[1], 7);
  route1.addNonDirectionalEdge(mainRoute->vertices[1], mainRoute->vertices[5], 8);

  Graph route2;

  route2.addVertex(mainRoute->vertices[0]);
  route2.addVertex(mainRoute->vertices[2]);
  route2.addVertex(mainRoute->vertices[6]);

  route2.addNonDirectionalEdge(mainRoute->vertices[0], mainRoute->vertices[2], 7);
  route2.addNonDirectionalEdge(mainRoute->vertices[2], mainRoute->vertices[6], 3);

  Graph route3;

  route3.addVertex(mainRoute->vertices[8]);
  route3.addVertex(mainRoute->vertices[10]);
  route3.addVertex(mainRoute->vertices[7]);
  route3.addVertex(mainRoute->vertices[9]);

  route3.addNonDirectionalEdge(mainRoute->vertices[8], mainRoute->vertices[10], 6);
  route3.addNonDirectionalEdge(mainRoute->vertices[10], mainRoute->vertices[7], 8);
  route3.addNonDirectionalEdge(mainRoute->vertices[7], mainRoute->vertices[9], 7);

  Graph route4;

  route4.addVertex(mainRoute->vertices[0]);
  route4.addVertex(mainRoute->vertices[1]);
  route4.addVertex(mainRoute->vertices[5]);

  route4.addNonDirectionalEdge(mainRoute->vertices[0], mainRoute->vertices[1], 7);
  route4.addNonDirectionalEdge(mainRoute->vertices[1], mainRoute->vertices[5], 8);

  Graph route5;

  route5.addVertex(mainRoute->vertices[0]);
  route5.addVertex(mainRoute->vertices[2]);
  route5.addVertex(mainRoute->vertices[7]);

  route5.addNonDirectionalEdge(mainRoute->vertices[0], mainRoute->vertices[2], 7);
  route5.addNonDirectionalEdge(mainRoute->vertices[2], mainRoute->vertices[7], 8);

  Graph route6;

  route6.addVertex(mainRoute->vertices[10]);
  route6.addVertex(mainRoute->vertices[8]);
  route6.addVertex(mainRoute->vertices[1]);
  route6.addVertex(mainRoute->vertices[7]);
  route6.addVertex(mainRoute->vertices[4]);
  route6.addVertex(mainRoute->vertices[3]);

  route6.addNonDirectionalEdge(mainRoute->vertices[10], mainRoute->vertices[8], 6);
  route6.addNonDirectionalEdge(mainRoute->vertices[8], mainRoute->vertices[1], 4);
  route6.addNonDirectionalEdge(mainRoute->vertices[1], mainRoute->vertices[7], 8);
  route6.addNonDirectionalEdge(mainRoute->vertices[7], mainRoute->vertices[4], 5);
  route6.addNonDirectionalEdge(mainRoute->vertices[4], mainRoute->vertices[3], 3);

  fastestRouteHistory->addGraph(route1);
  fastestRouteHistory->addGraph(route2);
  fastestRouteHistory->addGraph(route3);
  fastestRouteHistory->addGraph(route4);
  fastestRouteHistory->addGraph(route5);
  fastestRouteHistory->addGraph(route6);
}

void createStation(Graph &mainRoute)
{
  clearTerminal();
  cout << "===========================================================================" << endl;
  cout << "                                 Isi Form                                  " << endl;
  cout << "===========================================================================" << endl;
  cout << "Ketik '<' untuk kembali atau tekan enter untuk mengakhiri input" << endl;
  while (true)
  {
    string stationName = inputln("Masukan nama stasiun: ");
    string konfirmasi;

    if (stationName.empty())
    {
      cout << "\033[2K"; // Menghapus baris saat ini
      cout << "\033[1A";
      cout << "                                                            " << endl;
      cout << "\033[2K"; // Menghapus baris saat ini
      cout << "\033[1A";
      cout << MARK << MARK_INPUT<< "Akhiri inputan? (y/n): ";
      getline(cin, konfirmasi);

      if (konfirmasi.empty())
      {
          cout << "\033[2K"; // Menghapus baris saat ini
          cout << "\033[1A";
          cout << "                                                            " << endl;
          cout << "\033[2K"; // Menghapus baris saat ini
          cout << "\033[1A";
          cout << MARK_WARNING << MARK_OUTPUT << "Masukan y/n" << endl;
          this_thread::sleep_for(chrono::seconds(2));
          cout << "\033[2K"; // Menghapus baris saat ini
          cout << "\033[1A";
          continue;
      }
      else if (konfirmasi == "y")
      {
          break;
      }
      else if (konfirmasi == "n")
      {
          cout << "\033[2K"; // Menghapus baris saat ini
          cout << "\033[1A";
          cout << "                                                            " << endl;
          cout << "\033[2K"; // Menghapus baris saat ini
          cout << "\033[1A";
          continue;
      }
      else if (konfirmasi != "y" && konfirmasi != "n")
      {
          cout << "\033[2K"; // Menghapus baris saat ini
          cout << "\033[1A";
          cout << "                                                            " << endl;
          cout << "\033[2K"; // Menghapus baris saat ini
          cout << "\033[1A";
          cout << MARK_WARNING << MARK_OUTPUT << " Masukan y/n" << endl;
          this_thread::sleep_for(chrono::seconds(2));
          cout << "\033[2K"; // Menghapus baris saat ini
          cout << "\033[1A";
          continue;
      }
    }
    else if (stationName == "<")
    {
        return;
    }

    bool stationExists = false;
    for (const auto &vertex : mainRoute.vertices)
    {
        if (vertex->name == stationName)
        {
            stationExists = true;
            cout << MARK << MARK_OUTPUT << " Lokasi " << stationName << " sudah ada" << endl;
            this_thread::sleep_for(chrono::seconds(2));
            cout << "\033[2K"; // Menghapus baris saat ini
            cout << "\033[1A";
            cout << "                                                            " << endl;
            cout << "\033[2K"; // Menghapus baris saat ini
            cout << "\033[1A";
        }
    }

      if (!stationExists)
      {
          Vertex *newStation = new Vertex(stationName);
          mainRoute.addVertex(newStation);
      }
    }
    cout << "---------------------------------------------------------------------------" << endl;
    for (const auto &vertex : mainRoute.vertices) {
        cout << MARK << MARK_OUTPUT << "Stasiun " << vertex->name << " telah ditambahkan ke vertex" << endl;
    }
            
  clearConfirmation();
}


void viewStation(Graph &mainRoute)
{
  clearTerminal();

  // TODO (SIAPA AJA LAH): Buat fitur lihat stasiun
  println("Fitur ini belum tersedia... 😅");
  println("ZAMZAMI boleh langsung tambahin fungsinya di baris 394");

  clearConfirmation();
}

void createRoute(Graph &mainRoute) {
    clearTerminal();

    string firstStationName = inputln("Masukkan nama stasiun pertama: ");
    string secondStationName = inputln("Masukkan nama stasiun kedua: ");
    int weight = stoi(inputln("Masukkan jarak antara kedua stasiun (dalam KM): "));

    Vertex *firstStation = nullptr;
    Vertex *secondStation = nullptr;

    for (const auto &vertex : mainRoute.vertices) {
        if (vertex->name == firstStationName) {
            firstStation = vertex;
        }
        if (vertex->name == secondStationName) {
            secondStation = vertex;
        }
    }

    if (firstStation == nullptr || secondStation == nullptr) {
        println("Salah satu atau kedua stasiun tidak ditemukan.");
    } else if (mainRoute.addNonDirectionalEdge(firstStation, secondStation, weight)) {
        println("Rute berhasil ditambahkan antara " + firstStationName + " dan " + secondStationName + ".");
    } else {
        println("Rute sudah ada.");
    }

    clearConfirmation();
}

// Function to check if an item is not found in a vector
bool isNotFoundIn(const vector<Vertex *> items, const Vertex *item)
{
  return find(items.begin(), items.end(), item) == items.end();
}

void findFastestRoute(Graph &mainRoute, Queue &fastestRouteHistory) {
    clearTerminal();

    Vertex *startVertex = nullptr;
    Vertex *endVertex = nullptr;

    string startVertexName = inputln("Masukkan nama stasiun awal: ");
    for (const auto &vertex : mainRoute.vertices) {
        if (vertex->name == startVertexName) {
            startVertex = vertex;
            break;
        }
    }

    if (startVertex == nullptr) {
        println("Stasiun awal tidak ditemukan");
        clearConfirmation();
        return;
    }

    string endVertexName = inputln("Masukkan nama stasiun tujuan: ");
    for (const auto &vertex : mainRoute.vertices) {
        if (vertex->name == endVertexName) {
            endVertex = vertex;
            break;
        }
    }

    if (endVertex == nullptr) {
        println("Stasiun tujuan tidak ditemukan");
        clearConfirmation();
        return;
    }

  // MAIN DJIKTRA ALGORITHM

  // Step 1: Buat map shortestDistance yang berisi pasangan vertex dan pasangan vertex serta jarak terpendek
  map<Vertex *, pair<Vertex *, long long unsigned int>> shortestDistance;

  // Step 2: Inisialisasi shortestDistance dengan nilai awal vertex null dan jarak INFINITY
  for (const auto &vertex : mainRoute.vertices)
  {
    shortestDistance[vertex] = make_pair(nullptr, INFINITY);
  }

  // Step 3: Buat vector visitedVertices yang nantinya berisi vertex yang sudah dikunjungi
  vector<Vertex *> visitedVertices;

  // Step 4: Inisialisasi currentVertex dengan startVertex sebagai vertex yang akan berpindah-pindah
  Vertex *currentVertex = startVertex;
  // Step 5: Inisialisasi pasangan vertex awal dan jarak 0
  shortestDistance[currentVertex] = make_pair(currentVertex, 0);

  // Step 6: Looping sampai currentVertex sudah sampai di endVertex
  while (currentVertex != endVertex)
  {
    // Step 7: Tandai currentVertex sebagai vertex yang sudah dikunjungi ke dalam visitedVertices
    visitedVertices.push_back(currentVertex);

    // Step 8: Ambil semua edge dari currentVertex
    vector<Edge *> currentEdges = mainRoute.getEdges(currentVertex);

    // Step 9: Looping semua edge dari currentVertex
    for (const auto &edge : currentEdges)
    {
      // Step 10: Ambil vertex tujuan dari edge
      Vertex *destinationVertex = edge->secondVertex;

      // Step 11: Hitung jarak dari currentVertex ke destinationVertex
      long long unsigned int distance = shortestDistance[currentVertex].second + edge->weight;

      // Step 12: Jika jarak dari currentVertex ke destinationVertex lebih kecil dari jarak terpendek sebelumnya
      if (distance < shortestDistance[destinationVertex].second)
      {
        // Step 13: Update shortestDistance dengan jarak terpendek
        shortestDistance[destinationVertex] = make_pair(currentVertex, distance);
      }
    }

    // Step 14: Inisialisasi jarak terpendek dari kumpulan vertex yang belum dikunjungi dengan INFINITY
    long long unsigned int minDistance = INFINITY;

    // Step 15: Looping semua vertex yang belum dikunjungi
    for (const auto &vertex : mainRoute.vertices)
    {
      // Step 16: Jika jarak terpendek dari vertex lebih kecil dari jarak terpendek sebelumnya dan vertex tidak sama dengan vertex itu sendiri dan vertex belum dikunjungi
      if (shortestDistance[vertex].second < minDistance && shortestDistance[vertex].first != vertex && isNotFoundIn(visitedVertices, vertex))
      {
        // Step 17: Update jarak terpendek dengan jarak terpendek dari vertex
        minDistance = shortestDistance[vertex].second;
        // Step 18: Pindah ke vertex yang memiliki jarak terpendek
        currentVertex = vertex;
      }
    }
  }

  // AKHIR DARI ALGORITMA DJIKSTRA

  // Ambil total jarak dari startVertex ke endVertex
  const long long unsigned int totalDistance = shortestDistance[endVertex].second;

  // Buat graph untuk rute tercepat
  Graph fastestRoute;

  // Menelusuri dari vertex tujuan ke vertex awal
  // Looping dari vertex tujuan ke vertex awal (kebalikan dari sebelumnya)
  while (currentVertex != startVertex)
  {
    // Tambahkan vertex ke rute tercepat
    fastestRoute.addVertex(currentVertex);
    // Ambil vertex sebelumnya
    Vertex *previousVertex = shortestDistance[currentVertex].first;

    // Looping semua edge dari mainRoute
    for (const auto &edge : mainRoute.edges)
    {
      // Jika edge memiliki vertex yang sama dengan vertex sebelumnya dan vertex sekarang
      if ((edge->firstVertex == currentVertex && edge->secondVertex == previousVertex) || (edge->firstVertex == previousVertex && edge->secondVertex == currentVertex))
      {
        // Tambahkan edge ke rute tercepat
        fastestRoute.addNonDirectionalEdge(currentVertex, previousVertex, edge->weight);
        break;
      }
    }

    // Pindah ke vertex sebelumnya
    currentVertex = previousVertex;
  }

  // Tambahkan vertex awal ke rute tercepat
  fastestRoute.addVertex(startVertex);

  // Ubah rute tercepat menjadi urutan yang benar
  fastestRoute.reverseEdges();

  // Traversal atau Print rute tercepat
  for (const auto &edge : fastestRoute.edges)
  {
    cout << edge->firstVertex->name + " -> " + edge->secondVertex->name + " : " + to_string(edge->weight) + " KM" << std::endl;
  }

  cout << endl;

  println("Total jarak: " + to_string(totalDistance) + " KM");

  cout << endl;

  fastestRouteHistory.addGraph(fastestRoute);

  clearConfirmation();

}

void viewFastestRouteHistory(Queue &fastestRouteHistory)
{
  clearTerminal();

  long long unsigned int j = 1;
  for (const auto &graph : fastestRouteHistory.graphs)
  {

    println("Route " + std::to_string(j) + " :");

    long long unsigned int i = 0;
    int totalWeight = 0;
    for (const auto &edge : graph.edges)
    {
      // totalWeight += edge->weight;
      std::cout << edge->firstVertex->name + " -> " + edge->secondVertex->name + " : " + std::to_string(edge->weight) + " KM";
      if (i < graph.edges.size() - 1)
      {
        std::cout << " -> ";
      }
      else
      {
        std::cout << std::endl;
      }
      i++;
    }

    std::cout << std::endl;
    j++;
  }

  clearConfirmation();
}

void deleteRoute(Graph &mainRoute)
{
  clearTerminal();

  // TODO (Naila): Buat fitur cari rute tercepat dengan algoritma djiikstra
  println("Fitur ini belum tersedia... 😅");
  println("Naila boleh langsung tambahin fungsinya di baris 460");

  clearConfirmation();
}

void deleteStation(Graph &mainRoute)
{

  clearTerminal();

  // TODO (Rahma): Buat fitur cari rute tercepat dengan algoritma djiikstra
  println("Fitur ini belum tersedia... 😅");
  println("Rahma boleh langsung tambahin fungsinya di baris 478");

  clearConfirmation();
}

void exitOutput()
{
  for (int i = 0; i < 3; i++)
  {
    println("Keluar dari program");
    delay(256);
    clearTerminal();
    delay(128);
    println("Keluar dari program.");
    delay(256);
    clearTerminal();
    delay(128);
    println("Keluar dari program..");
    delay(256);
    clearTerminal();
    delay(128);
    println("Keluar dari program...");
    delay(256);
    clearTerminal();
    delay(128);
  }
  clearTerminal();
  println("Selamat tinggal... 🥹 🥹");
  delay(3000);
  clearTerminal();
}
