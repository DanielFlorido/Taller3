#include <fstream>
#include <iostream>
#include <math.h>
#include <string>
#include <vector>
using namespace std;

template <class _T> void leerArchivo(const string &nombreArchivo);

int main(int argc, char **argv) {
  if (argc > 3) {
    cerr << "Usage: " << argv[0] << "input byte/word" << endl;
    return -1;
  }
  string nombrearchivo = argv[1];
  string tipo = argv[2];
  if (tipo == "byte") {
    leerArchivo<unsigned char>(nombrearchivo);
  } else if (tipo == "word") {
    leerArchivo<unsigned short>(nombrearchivo);
  }
  return (0);
}

template <class _T> void leerArchivo(const string &nombreArchivo) {
  ifstream entrada(nombreArchivo.c_str(), ios::binary | ios::ate);
  unsigned long long size = entrada.tellg();
  entrada.seekg(0, ios::beg);

  vector<_T> data(size / sizeof(_T));
  char *buffer = reinterpret_cast<char *>(data.data());
  entrada.read(buffer, data.size() * sizeof(_T));
  entrada.close();

  // Histograma
  vector<double> H((1 << ((sizeof(_T)) << 3)), 0);
  for (unsigned long long i = 0; i < data.size(); ++i) {
    H[data[i]] += double(1) / (double(data.size()));
  }
  for (unsigned long long i = 0; i < H.size(); ++i) {
    if (H[i] != 0) {
      cout << i << " " << H[i] << endl;
    }
  }
}
