# Dataset source and preparation

{
  "source": "https://www.kaggle.com/datasets/tmdb/tmdb-movie-metadata",
  "records": 4803,
  "archive_sha256": "0342a9748128f44e6a58e96af19d918478af73a8976b142aa4e7e0aa3c50ef1b"
}

All 4,803 movie rows are retained in source order. rating = vote_average (0-10); release_year = first four characters of release_date, or 0 when missing; popularity = the original decimal TMDB popularity. Zero ratings remain and do not imply a recommended film. Quoted titles containing commas are preserved.
