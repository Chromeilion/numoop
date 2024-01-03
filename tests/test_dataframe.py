import numoop


class TestDataFrame:
    CSV_PATH = "./tests/dataset.csv"

    def test_load_csv(self) -> None:
        types, df = numoop.load(self.CSV_PATH, True)
        first_col = df[0]
        a = "b"
