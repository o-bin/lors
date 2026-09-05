// ==========================================
// Modular Math Library - Statistical Functions
// Subdirectory: analytics/
// ==========================================

incorporate "../core/types.inc"

algorithm stats_min(data : sequence<precise>) -> precise
begin
    datum n : whole = length(data);
    verify (n == 0) then result 0.0; conclude
    datum m : precise = data[0];
    datum i : whole = 1;
    cycle (i < n) do
        datum val : precise = data[i];
        verify (val < m) then
            m = val;
        conclude
        i = i + 1;
    conclude
    result m;
end

algorithm stats_max(data : sequence<precise>) -> precise
begin
    datum n : whole = length(data);
    verify (n == 0) then result 0.0; conclude
    datum m : precise = data[0];
    datum i : whole = 1;
    cycle (i < n) do
        datum val : precise = data[i];
        verify (val > m) then
            m = val;
        conclude
        i = i + 1;
    conclude
    result m;
end

algorithm stats_mean(data : sequence<precise>) -> precise
begin
    datum n : whole = length(data);
    verify (n == 0) then result 0.0; conclude
    datum sum : precise = 0.0;
    datum i : whole = 0;
    cycle (i < n) do
        sum = sum + data[i];
        i = i + 1;
    conclude
    result sum / to_precise(to_string(n));
end

algorithm stats_variance(data : sequence<precise>, avg : precise) -> precise
begin
    datum n : whole = length(data);
    verify (n == 0) then result 0.0; conclude
    datum sum_sq : precise = 0.0;
    datum i : whole = 0;
    cycle (i < n) do
        datum diff : precise = data[i] - avg;
        sum_sq = sum_sq + diff * diff;
        i = i + 1;
    conclude
    result sum_sq / to_precise(to_string(n));
end

algorithm stats_compute(data : sequence<precise>) -> StatsResult
begin
    datum n : whole = length(data);
    datum min_v : precise = stats_min(data);
    datum max_v : precise = stats_max(data);
    datum avg : precise = stats_mean(data);
    datum var : precise = stats_variance(data, avg);
    datum sdev : precise = root(var);
    result StatsResult(n, min_v, max_v, avg, var, sdev);
end
