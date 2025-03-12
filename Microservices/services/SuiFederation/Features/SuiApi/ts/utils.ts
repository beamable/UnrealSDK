import {InputParams, PaginatedResult} from "./models";
import {GasCostSummary} from "@mysten/sui/client";

export async function retrievePaginatedData<T, V>(getData: ((input: T) => Promise<V>), input: T) {
    let allResults: V[] = [];
    let nextPage: string | null = null;

    function isResultObject(obj: unknown): obj is PaginatedResult<V> {
        return typeof obj === 'object' && obj !== null;
    }
    function isInputObject(obj: unknown): obj is InputParams {
        return typeof obj === 'object' && obj !== null;
    }

    let data = await getData(input);
    allResults = allResults.concat(data);

    if (isResultObject(data) && 'hasNextPage' in data) {
        const hasNext= data.hasNextPage;
        if (hasNext && 'nextCursor' in data) {
            const nextCursor = data.nextCursor;
            if (nextCursor !== null && nextCursor !== undefined) {
                nextPage = nextCursor;
            }
        }
    }

    while (nextPage != null) {
        if (isInputObject(input) && 'cursor' in input) {
            input.cursor = nextPage;
            data = await getData(input);
            allResults = allResults.concat(data);
            if (isResultObject(data) && 'hasNextPage' in data) {
                const hasNext= data.hasNextPage;
                if (hasNext && 'nextCursor' in data) {
                    const nextCursor = data.nextCursor;
                    if (nextCursor !== null && nextCursor !== undefined) {
                        nextPage = nextCursor;
                    }
                } else {
                    nextPage = null;
                }
            } else {
                nextPage = null;
            }
        }
    }
    return allResults;
}

export function calculateTotalCost(gasSummary: GasCostSummary): string {
    const computationCost = parseFloat(gasSummary.computationCost) || 0;
    const storageCost = parseFloat(gasSummary.storageCost) || 0;
    const storageRebate = parseFloat(gasSummary.storageRebate) || 0;
    const totalCost = computationCost + storageCost - storageRebate;
    return totalCost.toString();
}
export function stringToNumber(str: string): number {
    const num = Number(str);
    if (isNaN(num) || !Number.isSafeInteger(num)) {
        return 0;
    }
    return num;
}