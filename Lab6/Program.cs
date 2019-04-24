using System;

namespace Lab6 {
    class Program {
        public delegate double Func(int i, int j);
        static Random rnd = new Random();
        static void Main(string[] args) {
            try {
                Func<int, int, double> func;
                func = Rand;
                double[,] arr = { { 1.0, 2.0 } , { 3.0, 4.0 } };
                Matrix m = new Matrix(2, 2, arr);
                Matrix m1 = new Matrix(2, 2, func);
                Matrix m2 = new Matrix(2, 2, 1.0, 2.0, 3.0, 4.0);
                Matrix m3 = new Matrix(2, 1.0, 2.0, 3.0, 50.0);
                m = m2 + m3;
                Console.WriteLine(m);
                Console.WriteLine("{0,10:F3}", m1);
                Console.WriteLine(m2.ToString());
                Console.WriteLine(m3.ToString());
            }
            catch (Exception ex) {
                Console.WriteLine(ex.Message);
            }
        }
        private static double Rand(int i, int j) {
            return rnd.Next(0, 10);
        }
    }
}
