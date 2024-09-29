
import unittest
from main import bellman_ford

class Test(unittest.TestCase):
    def test_bellman_ford(self):
        self.assertEqual(bellman_ford(4, [[0, 0, 0, 0, 0], [0, 0, 1, 0, 0], [0, 0, 0, 2, 0], [0, 0, 0, 0, 3], [0, 0, 0, 0, 0]]), [[0, 0, 1, 3, 6], [0, 0, 1, 3, 6], [0, 0, 0, 2, 5], [0, 0, 0, 0, 3], [0, 0, 0, 0, 0]])
        self.assertEqual(bellman_ford(4, [[0, 0, 0, 0, 0], [0, 0, -1, 0, 0], [0, 0, 0, -2, 0], [0, 0, 0, 0, -3], [0, 0, 0, 0, 0]]), "Negative cost cycle")
        self.assertEqual(bellman_ford(4, [[0, 0, 0, 0, 0], [0, 0, 1, 0, 0], [0, 0, 0, 2, 0], [0, 0, 0, 0, 3], [0, 0, 0, 0, 0], [0, 0, 0, 0, 0]]), [[0, 0, 1, 3, 6], [0, 0, 1, 3, 6], [0, 0, 0, 2, 5], [0, 0, 0, 0, 3], [0, 0, 0, 0, 0]])
        self.assertEqual(bellman_ford(4, [[0, 0, 0, 0, 0], [0, 0, 1, 0, 0], [0, 0, 0, 2, 0], [0, 0, 0, 0, 3], [0, 0, 0, 0, 0], [0, 0, 0, 0, 0]]), [[0, 0, 1, 3, 6], [0, 0, 1, 3, 6], [0, 0, 0, 2, 5], [0, 0, 0, 0, 3], [0, 0, 0, 0, 0]])

if __name__ == '__main__':
    unittest.main()
