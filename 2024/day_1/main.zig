const std = @import("std");

pub fn main() !void {
    const file = try std.fs.cwd().openFile("input.txt", .{});
    defer file.close();

    const line_len: u8 = 14; // 14 bytes per line including newline
    const lines: u16 = 1000; // No. lines
    var buffer: [lines * line_len]u8 = undefined; // File size = 14kB
    _ = try file.readAll(&buffer);

    var left_list: [lines]u32 = undefined;
    @memset(&left_list, 0);

    var right_list: [lines]u32 = undefined;
    @memset(&right_list, 0);

    for (0..(buffer.len / line_len)) |i| {
        const line: []const u8 = buffer[(i * line_len)..((i + 1) * line_len)];
        // std.debug.print("i={d} (len={d}): {s}", .{ i, line.len, line });

        const left: u32 = try std.fmt.parseInt(u32, line[0..5], 10);
        const right: u32 = try std.fmt.parseInt(u32, line[8 .. line_len - 1], 10);

        // std.debug.print("Left: {d}, Right: {d}\n", .{ left, right });

        left_list[i] = left;
        right_list[i] = right;
    }

    std.sort.pdq(u32, left_list[0..], {}, std.sort.asc(u32));
    std.sort.pdq(u32, right_list[0..], {}, std.sort.asc(u32));

    // --- Part one
    // var rv: u64 = 0;
    // for (0..lines) |i| {
    //     rv += @abs(@as(i64, left_list[i]) - @as(i64, right_list[i]));
    // }
    // std.debug.print("Result: {d}", .{rv});

    // --- Part two
    var rv: u64 = 0;
    for (left_list) |num| {
        var count: u32 = 0;
        var idx: usize = find_index(&right_list, num) orelse continue;

        while ((idx < right_list.len) and (right_list[idx] == num)) {
            count += 1;
            idx += 1;
        }

        std.debug.print("Num: {d} | Occurences: {d}\n", .{ num, count });
        rv += num * count;
    }
    std.debug.print("Result: {d}", .{rv});
}

pub fn find_index(arr: []const u32, num: u32) ?usize {
    for (0..arr.len) |i| {
        if (arr[i] == num) {
            return i;
        }
    }

    return null;
}
