"""
This is an example project demonstrating the functionality of the DataFrame and
load functions in numoop.
"""
from numoop import load, utils
from scipy.stats import mode
import matplotlib.pyplot as plt


dataset_path = "./jobs_in_data.csv"

# Let's load the dataset
df = load(dataset_path, header=True)

# We can have a look at the DataFrame summary:
df.summarize()

# Let's have a look at some of the different job titles:
print(f"\nSome job titles: \n{list(df.get_map(1).values())[:5]}\n")

# Since I find computer vision cool, let's see how large the average salary is
# for a "Computer Vision Engineer".
job_name = "Computer Vision Engineer"
df_m = df.get_map(1)
cve_idx = utils.get_key(df_m, job_name)
avg_salary = df.view("salary_in_usd")[df.view("job_title") == cve_idx].mean()
print(f"Average salary for a {job_name}: \n{avg_salary}\n")

# Not bad, but there must be a better paid job out there. Let's find the best
# paid data scientist profession:
avg_salaries: list[tuple[str, float]] = []
for cve_idx, job in df_m.items():
    avg_salaries.append(
        (job, df.view("salary_in_usd")[df.view("job_title") == cve_idx].mean())
    )

best_paid = sorted(avg_salaries, key=lambda x: x[1])[-1]
print(f"The best paid data science job is: \n"
      f"{best_paid[0]}\n"
      f"With an average salary of: \n"
      f"{best_paid[1]}\n")

# Wow, that's a decent pay! Let's see how many people have this job:
no_top_people = df.view("experience_level")[
    df.view("job_title") == utils.get_key(df_m, best_paid[0])].shape[0]

print(f"Number of people working as a {best_paid[0]}: \n"
      f"{no_top_people}\n")

# That's not many people, let's try looking at a job that more people have.
# To do this, we can find the highest paying job with more than 400 people in
# it.
job_title_view = df.view("job_title")
threshold = 400
for job, salary in sorted(avg_salaries, key=lambda x: x[1])[::-1]:
    no_people = job_title_view[job_title_view == utils.get_key(df_m, job)].shape[0]
    if no_people > threshold:
        best_paid_better = job, salary, no_people
        break

print(f"The best paid job with more than {threshold} people in it "
      f"({best_paid_better[2]} people) is: \n"
      f"{best_paid_better[0]}\n"
      f"With a salary of: \n"
      f"{round(best_paid_better[1], 2)}\n")

# Let's find what the most common data science job is:
most_common_job_idx, no_most_common_job = mode(df.view("job_title"))
most_common_job_percentage = no_most_common_job[0] / df.view("job_title").shape[0] * 100
most_common_job = df_m[most_common_job_idx[0]]
most_common_avg_salary = [
    i[1] for i in avg_salaries if i[0] == most_common_job][0]
print(f"The most common data science job employing "
      f"{round(most_common_job_percentage, 2)}% people is: \n"
      f"{most_common_job}\n"
      f"With an average salary of: \n "
      f"{round(most_common_avg_salary, 2)}\n")

# Let's make a pie chart to see how job experience requirements are distributed:
fig, ax = df.make_plot("experience_level", "pie")
ax.set_title("Required Experience For Data Science Jobs")
plt.show()

# We can also look at a histogram of salaries:
df.make_plot("salary_in_usd", "hist")
plt.show()
