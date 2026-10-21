# Dataset source and preparation

{
  "source": "https://www.kaggle.com/datasets/patrickb1912/ipl-complete-dataset-20082020",
  "records": 2617,
  "delivery_rows": 260920,
  "excluded_super_over_rows": 161,
  "seasons": [
    "2008",
    "2009",
    "2010",
    "2011",
    "2012",
    "2013",
    "2014",
    "2015",
    "2016",
    "2017",
    "2018",
    "2019",
    "2020",
    "2021",
    "2022",
    "2023",
    "2024"
  ],
  "archive_sha256": "05810fbec9913ec587e92457c8ae97527e00a7040cd7fe8008212a1d5410fd57"
}

Each row is one batter-team-season aggregate, not a unique career total. Runs sum batsman_runs from regular innings (1 and 2); extras are excluded. Season uses the match date calendar year (2008-2024). Super overs are excluded. Players with zero runs remain. Original names/team names are preserved; no artificial duplicates were added. IPLBatters.csv is not limited to IPL 2025.
