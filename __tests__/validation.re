open Jest;

/* This is just a demonstration of using jest for testing */
let () =
  describe "Medium validation"
    ExpectJs.(fun () => {
      test "should demonstrate a test a reason" (fun () => 
        expect(Demo.doSomething "withArgs") |> toEqual "expectedOutput"
      );
    });