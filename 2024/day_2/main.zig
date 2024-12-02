const std = @import("std");

fn main() !void {
    const file = try std.fs.cwd().openFile("input.txt", .{});
    defer file.close();

    var buffer: [60]u8 = undefined;
    _ = try file.readAll(&buffer);
    var lines = std.mem.splitScalar(u8, &buffer, '\n');

    var rv: u32 = 0;
    outer: while (lines.next()) |report| {
        if (report.len < 1) {
            break;
        }

        var levels = std.mem.splitScalar(u8, report[0..], ' ');
        std.debug.print("{s}\n", .{levels.buffer});

        const first: u32 = try std.fmt.parseInt(u32, levels.next().?, 10);
        const second: u32 = try std.fmt.parseInt(u32, levels.next().?, 10);
        std.debug.print("Comparing {d} and {d}\n", .{ first, second });

        const diff: i64 = @as(i64, first) - @as(i64, second);
        if (@abs(diff) < 1 or @abs(diff) > 3) {
            continue;
        }

        var prev: u32 = second;
        while (levels.next()) |level| {
            const curr = try std.fmt.parseInt(u32, level, 10);
            std.debug.print("Comparing {d} and {d}\n", .{ prev, curr });
            const curr_diff: i64 = @as(i64, prev) - @as(i64, curr);

            if ((curr_diff < 0 and diff > 0) or (curr_diff > 0 and diff < 0)) {
                continue :outer;
            } else if (@abs(curr_diff) > 3 or @abs(curr_diff) < 1) {
                std.debug.print("Diff: {d}\n", .{curr_diff});
                continue :outer;
            }

            prev = curr;
        }

        std.debug.print("Report OK\n", .{});
        rv += 1;
    }

    std.debug.print("Result: {d}", .{rv});
}
