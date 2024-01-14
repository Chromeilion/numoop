import numoop
from numoop.stats import DataFrame
import numpy as np
import numpy.typing as npt
import pytest
import pickle
import matplotlib.testing
import matplotlib.testing.compare
import tempfile


class TestDataFrame:
    PLOT_DIR = "./tests/correct_plots"

    def test_init(self) -> None:
        # Init without anything
        df = DataFrame()
        assert df.shape == (0, 0)
        # Init with arguments
        df = DataFrame([[0, 2.0, 100], [10, 11.11, 12]])
        assert df.shape == (2, 3)
        assert np.all((df[0] == np.array([[0], [10]])))

    def test_column_labels(self) -> None:
        labels = ["col1", "col2", "col3"]
        # Init with labels should work as expected.
        df = DataFrame([[0, 2.0, 100],
                               [10, 11.11, 12]], labels)
        assert df.column_labels == labels
        assert np.all(df("col1") == np.array([[0], [10]]))
        other_labels = ["c1", "c2", "c3"]
        # Test label setter
        df.column_labels = other_labels
        assert np.all(df("c3") == np.array([[100], [12]]))
        # Try testing incorrect number of labels
        with pytest.raises(ValueError):
            df.column_labels = ["c1", "c2", "c3", "c4"]
        with pytest.raises(ValueError):
            df.column_labels = ["c1", "c2"]

    def test_append_row(self) -> None:
        df = DataFrame()
        # Appending to an empty DataFrme
        df.append_row([5.5, 1, 4, 7.7])
        # Make sure the values were set correctly
        assert np.isclose(df[0][0], 5.5) and np.isclose(df[3][0], 7.7)
        assert df[1][0] == 1 and df[2][0] == 4
        # Now that we have a row, appending incorrect types or row size should
        # give errors.
        with pytest.raises(ValueError):
            df.append_row([3, 3, 4.5, 7.7])
        with pytest.raises(ValueError):
            df.append_row([1., 2, 3, 4., 5])
        # Make sure the shape is still correct
        assert df.shape == (1, 4)
        # Try appending a second row, check values again.
        df.append_row([5.6, 2, 5, 8.8])
        assert df.shape == (2, 4)
        assert np.isclose(df[0], np.array([[5.5], [5.6]])).all()
        df_2 = DataFrame()
        # We should also be able to use a numpy array to add rows.
        np_row: npt.NDArray[np.int_] = np.array([1, 2, 3, 4])
        df_2.append_row(np_row)
        assert (df_2[0][0] == 1 and df_2[1][0] == 2 and df_2[2][0] == 3 and
                df_2[3][0] == 4)

    def test_insert_row(self) -> None:
        df = DataFrame()
        # Insert a row into an empty DataFrame
        df.insert_row([5, 1.3, 4.4, 7], 0)

        # Inserting incorrect types should raise an error.
        with pytest.raises(ValueError):
            df.insert_row([1, 2.3, 3, 4], 1)
        # Inserting an incorrectly sized row should give an error.
        with pytest.raises(ValueError):
            df.insert_row([1, 2.3, 3.4, 4, 5], 1)
        # Inserting a row out of bounds should also give an error.
        with pytest.raises(IndexError):
            df.insert_row([1, 2.3, 3.4, 4], 100)
        # Make sure the shape is correct.
        assert df.shape == (1, 4)
        # Insert a second row and do checks again
        df.insert_row([6, 2.0, 5.3, 8], 0)
        assert df.shape == (2, 4)
        assert np.all(df[0] == np.array([6, 5])[:, None])

    def test_append_column(self) -> None:
        df = DataFrame()
        # Append a column to an empty DataFrame.
        df.append_column(np.array([[5], [1], [4], [7]]))
        # Appending column with an incorrect number of rows.
        with pytest.raises(ValueError):
            df.append_column(np.array([[1], [2], [3], [4], [5]]))
        # Make sure shape is correct.
        assert df.shape == (4, 1)
        # Append second column and check values and shape.
        df.append_column(np.array([[5.6], [2.0], [5.3], [8.8]]))
        assert df.shape == (4, 2)
        assert np.all(df[0] == np.array([[5], [1], [4], [7]]))

    def test_insert_column(self) -> None:
        df = DataFrame()
        # Insert column into an empty DataFrame.
        df.insert_column(np.array([[5], [1], [4], [7]]), 0)
        # Inserting an incorrect number of rows gives an error.
        with pytest.raises(ValueError):
            df.insert_column(np.array([[1], [2], [3], [4], [5]]), 1)
        # Inserting out of bounds raises an error.
        with pytest.raises(IndexError):
            df.insert_column(np.array([[1], [2], [3], [4]]), 100)
        # Check shape of the DataFrame.
        assert df.shape == (4, 1)
        # Insert second column and check values/shape.
        df.insert_column(np.array([[5.6], [2.0], [5.3], [8.8]]), 0)
        assert df.shape == (4, 2)
        assert np.all(df[1] == np.array([[5], [1], [4], [7]]))

    def test_indexing(self) -> None:
        df = DataFrame([[5, 12.6, 4, 65.2],
                        [1, 55.0, 7, 99.9]])
        # Make sure indexing gives us what we expect.
        assert np.all(df[0] == np.array([[5], [1]]))
        # Take a column out of the DataFrame, change a value, and then reinsert
        # it.
        col = df[0]
        col[1, 0] = 10
        df[0] = col
        assert df[0][1, 0] == 10
        # Trying to set a column with an incorrect number of rows gives an
        # error.
        arr = np.zeros((100, 1))
        with pytest.raises(ValueError):
            df[0] = arr

    def test_dtypes(self) -> None:
        df = DataFrame()

        # Now lets make sure that no hidden type conversions are happening.
        int_ = np.array([[21], [100]], dtype=np.intc)
        long_int = np.array([[21], [100]], dtype=np.int_)
        long_long_int = np.array([[20001], [10]], dtype=np.longlong)
        single = np.array([[22.2], [55.5]], dtype=np.single)
        double = np.array([[23.002], [55.504]], dtype=np.double)
        cx_single = np.array([[33.3 + 10j], [55.5 + 200j]], dtype=np.csingle)
        cx_double = np.array([[44.3 + 100j], [604.2 + 67j]], dtype=np.cdouble)

        cols: list[numoop.types.sup_col_arr_types] = [
            int_, long_int, long_long_int, single, double, cx_single, cx_double
        ]

        list(map(df.append_column, cols))
        assert all([df[i].dtype == cols[i].dtype for i in range(len(cols))])

        # Inserting an invalid type should raise an error.
        bool_ = np.array([[True], [False]], dtype=np.bool_)
        with pytest.raises(TypeError):
            df.append_column(bool_)  # type: ignore

    def test_view(self) -> None:
        df = DataFrame([[5, 12.6, 4, 65.2],
                        [1, 55.0, 7, 99.9]],
                        labels=["col1", "col2", "col3", "col4"])
        # Make sure the view has the correct values.
        assert np.all(df.view(0) == np.array([[5], [1]]))
        # We should also be able to access a column with it's label:
        assert np.all(df.view("col3") == np.array([[4], [7]]))

        # Editing a view is not allowed.
        with pytest.raises(ValueError):
            df.view(0)[1] = 10

    def test_pickle(self) -> None:
        labs = ["col1", "col2", "col3", "col4"]
        df = DataFrame([[0, 12.6, 4, 65.2],
                        [1, 55.0, 7, 99.9]],
                              labs)
        cat_map = {0: "cat1", 1: "cat2"}
        df.set_map(0, cat_map)
        # Pickle data
        data = pickle.dumps(df, -1)
        # Unplickle data
        df_unpickled = pickle.loads(data)
        # Make sure all unpickled data is correct.
        assert np.all(df[0] == df_unpickled[0])
        assert np.all(np.isclose(df[1], df_unpickled[1]))
        assert np.all(df[2] == df_unpickled[2])
        assert np.all(np.isclose(df[3], df_unpickled[3]))
        assert df_unpickled.column_labels == labs
        assert df_unpickled.get_map(0) == cat_map

    def test_set_map(self) -> None:
        df = DataFrame([[1, 12.6, 0],
                        [1, 55.0, 2],
                        [0, 33.1, 3]])
        cat_map_one = {0: "cat1", 1: "cat2"}
        cat_map_two = {0: "cat3", 1: "cat4", 2: "cat5", 3: "cat6"}

        df.set_map(0, cat_map_one)
        assert df.get_map(0) == cat_map_one

        with pytest.raises(IndexError):
            df.set_map(20, cat_map_two)

        df.set_map(2, cat_map_two)
        assert df.get_map(2) == cat_map_two
        assert df.get_map(0) == cat_map_one

    def test_plots(self) -> None:
        df = DataFrame([[1, 12.6, 0],
                        [1, 55.0, 2],
                        [0, 33.1, 3],
                        [0, 50.5, 3],
                        [0, 22.2, 0]])
        df.set_map(0, {0: "cat1", 1: "cat2"})
        df.column_labels = ["First Column", "Second Column", "Third Column"]

        plot_args = [(1, "hist"), (0, "bar"), (2, "bar"), (1, "line"),
                     (0, "pie")]

        # Improve reproducibility
        matplotlib.testing.setup()
        with tempfile.TemporaryDirectory() as f:
            for file_no, (idx, plot_type) in enumerate(plot_args):
                fig, ax = df.make_plot(idx, plot_type)
                file_name = f"fig{str(file_no)}.png"
                temp_fig_path = f"{f}/{file_name}"
                true_fig_path = f"{self.PLOT_DIR}/{file_name}"
                fig.savefig(temp_fig_path)
                assert matplotlib.testing.compare.compare_images(
                    true_fig_path, temp_fig_path, 0.001
                ) is None

        invalid_calls = [(1, "pie"), (1, "bar")]
        for idx, plot_type in invalid_calls:
            with pytest.raises(TypeError):
                df.make_plot(idx, plot_type)

        with pytest.raises(AttributeError):
            df.make_plot(0, "invalid_plot_type")


class TestLoadCSV:
    CSV_PATH = "./tests/dataset.csv"
    CSV_CORRECT_LABELS = [
        '\ufeffMarital status', 'Application mode', 'Application order',
        'Course', 'Daytime/evening attendance', 'Previous qualification',
        'Nationality', "Mother's qualification", "Father's qualification",
        "Mother's occupation", "Father's occupation", 'Displaced',
        'Educational special needs', 'Debtor', 'Tuition fees up to date',
        'Gender', 'Scholarship holder', 'Age at enrollment', 'International',
        'Curricular units 1st sem (credited)',
        'Curricular units 1st sem (enrolled)',
        'Curricular units 1st sem (evaluations)',
        'Curricular units 1st sem (approved)',
        'Curricular units 1st sem (grade)',
        'Curricular units 1st sem (without evaluations)',
        'Curricular units 2nd sem (credited)',
        'Curricular units 2nd sem (enrolled)',
        'Curricular units 2nd sem (evaluations)',
        'Curricular units 2nd sem (approved)',
        'Curricular units 2nd sem (grade)',
        'Curricular units 2nd sem (without evaluations)',
        'Unemployment rate', 'Inflation rate', 'GDP', 'Target']

    def test_full_load(self) -> None:
        df = numoop.stats.load(self.CSV_PATH, header=True)
        assert df.column_labels == self.CSV_CORRECT_LABELS
        first_col = df[0]
        assert df.shape == (499, 35)
        assert first_col.shape[0] == 499
        assert first_col.dtype.name == 'int64'
        assert df[df.shape[1]-2].dtype.name == 'float32'

        catmap = df.get_map(df.shape[1]-1)
        assert isinstance(catmap, dict)
        assert catmap[0] == "Dropout"
        assert catmap[1] == "Graduate"
        assert catmap[2] == "Enrolled"

        # We should also be able to load into a DataFrame
        df = DataFrame()
        numoop.stats.load(self.CSV_PATH, df, True)

    def test_partial_load(self) -> None:
        df = numoop.stats.load(self.CSV_PATH, header=True, columns=[1, 6])
        assert df.column_labels == [self.CSV_CORRECT_LABELS[1],
                                    self.CSV_CORRECT_LABELS[6]]
        first_col = df[0]
        assert df.shape == (499, 2)
        assert first_col.shape[0] == 499
        assert first_col.dtype.name == 'int64'
        assert df[df.shape[1]-2].dtype.name == 'int64'
